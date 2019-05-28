#include "stdafx.h"
#include "AnonymousPipe2.h"
#include <tchar.h>
#include <stdio.h>
#include <tchar.h>
#include <string>
#include <iostream>

#define SYSTEM_PAUSE system("pause")
#define EXCEPTIION_STATE_CHECK \
    if (!m_bInit) return E_NOTIMPL


CCmdHandler::CCmdHandler()
    : m_bInit(FALSE)
    , m_dwErrorCode(0)
    , m_hPipeRead(NULL)
    , m_hPipeWrite(NULL)
{
    ZeroMemory(m_szReadBuffer, sizeof(m_szReadBuffer));
    ZeroMemory(m_szWriteBuffer, sizeof(m_szWriteBuffer));
    ZeroMemory(&m_CommandParam, sizeof(m_CommandParam));
}

CCmdHandler::~CCmdHandler()
{
}

HRESULT CCmdHandler::Initalize()
{
    // 初始化，创建匿名管道
    if (m_bInit)
        return S_OK;

    m_bInit = TRUE;
    ZeroMemory(m_szReadBuffer, sizeof(m_szReadBuffer));
    ZeroMemory(&m_startupInfo, sizeof(STARTUPINFO));
    ZeroMemory(&m_processInfo, sizeof(PROCESS_INFORMATION));

    ZeroMemory(&m_saOutPipe, sizeof(m_saOutPipe));
    m_saOutPipe.nLength = sizeof(SECURITY_ATTRIBUTES);
    m_saOutPipe.lpSecurityDescriptor = NULL;
    m_saOutPipe.bInheritHandle = TRUE;
    if (!CreatePipe(&m_hPipeRead, &m_hPipeWrite, &m_saOutPipe, PIPE_BUFFER_SIZE))
    {
        m_dwErrorCode = GetLastError();
        return E_FAIL;
    }

    return S_OK;
}

HRESULT CCmdHandler::Finish()
{
    EXCEPTIION_STATE_CHECK;

    if (m_hPipeRead)
    {
        CloseHandle(m_hPipeRead);
        m_hPipeRead = NULL;
    }

    if (m_hPipeWrite)
    {
        CloseHandle(m_hPipeWrite);
        m_hPipeWrite = NULL;
    }

    return S_OK;
}

HRESULT CCmdHandler::HandleCommand(CHCmdParam* pCommmandParam)
{
    EXCEPTIION_STATE_CHECK;

    if (!pCommmandParam || pCommmandParam->iSize != sizeof(CHCmdParam))
        return E_INVALIDARG;

    if (_tcslen(pCommmandParam->szCommand) <= 0)
        return E_UNEXPECTED;

    memset(&m_CommandParam, 0, sizeof(m_CommandParam));
    m_CommandParam = *pCommmandParam;

    return ExecuteCmdWait();
}

HRESULT CCmdHandler::ExecuteCmdWait()
{
    EXCEPTIION_STATE_CHECK;

    HRESULT hResult = E_FAIL;
    DWORD dwReadLen = 0;
    DWORD dwStdLen = 0;

    ZeroMemory(&m_startupInfo, sizeof(STARTUPINFO));
    m_startupInfo.cb = sizeof(STARTUPINFO);
    GetStartupInfo(&m_startupInfo);

    m_startupInfo.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW; 
    m_startupInfo.hStdInput = m_hPipeRead;
    m_startupInfo.hStdOutput = m_hPipeWrite;
    m_startupInfo.hStdError = m_hPipeWrite;
    m_startupInfo.wShowWindow = SW_HIDE;

    DWORD dTimeOut = m_CommandParam.iTimeOut >= 3000 ? m_CommandParam.iTimeOut : 5000;

    do
    {
        if (!CreateProcess(NULL, m_CommandParam.szCommand, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &m_startupInfo, &m_processInfo))
        {
            m_dwErrorCode = GetLastError();
            hResult = E_FAIL;
            break;
        }

        DWORD dwRet = WaitForSingleObject(m_processInfo.hProcess, dTimeOut);
        if (WAIT_TIMEOUT == dwRet)
        {
            m_dwErrorCode = GetLastError();
            hResult = CO_E_SERVER_START_TIMEOUT;
            if (m_CommandParam.OnCmdEvent)
                m_CommandParam.OnCmdEvent(&m_CommandParam, CO_E_SERVER_START_TIMEOUT, "");
            break;
        }

        // 预览管道中数据的内容
        if (PeekNamedPipe(m_hPipeRead, NULL, 0, NULL, &dwReadLen, NULL) && dwReadLen > 0)
        {
            ZeroMemory(m_szPipeOut, sizeof(m_szPipeOut));

            // 读取管道中的数据
            if (ReadFile(m_hPipeRead, m_szPipeOut, dwReadLen, &dwStdLen, NULL))
            {
                hResult = S_OK;
                if (m_CommandParam.OnCmdEvent)
                    m_CommandParam.OnCmdEvent(&m_CommandParam, S_OK, m_szPipeOut);
            }
            else
            {
                m_dwErrorCode = GetLastError();
            }
        }
        else
        {
            m_dwErrorCode = GetLastError();
            hResult = E_FAIL;
        }
    } while (0);

    if (m_processInfo.hThread)
    {
        CloseHandle(m_processInfo.hThread);
        m_processInfo.hThread = NULL;
    }

    if (m_processInfo.hProcess)
    {
        CloseHandle(m_processInfo.hProcess);
        m_processInfo.hProcess = NULL;
    }

    return hResult;
}


void OnCommandEvent(const CHCmdParam* pParam, HRESULT hResultCode, char* szResult)
{
    if (!szResult || !szResult[0]) 
        return;

    if (!pParam || hResultCode != S_OK) 
        return;

    printf("============== 回调 ==============\n");
    std::string echo_data(szResult);
    std::string s_ok("S_OK");
    std::string::size_type pos = echo_data.find(s_ok);
    if (pos != std::string::npos)
        printf("命令执行成功\n");
    else
        printf("命令执行失败\n");
    printf("执行返回的结构:\n");
    printf("========================================\n");
    printf("%s\n", szResult);
}


int CommunicatWithAnonymousPipe2()
{
    CHCmdParam cmdParam;
    CCmdHandler cmdHandler;
    HRESULT cmdResult = S_OK;

    ZeroMemory(&cmdParam, sizeof(cmdParam));
    cmdParam.iSize = sizeof(CHCmdParam);

    TCHAR* szCmd = _T("c:\\windows\\system32\\cmd.exe /c ping www.baidu.com && echo S_OK || echo E_FAIL");
    _tcscpy_s(cmdParam.szCommand, szCmd);
    cmdParam.OnCmdEvent = OnCommandEvent;
    cmdParam.iTimeOut = 10000;

    cmdResult = cmdHandler.Initalize();
    if (cmdResult != S_OK)
    {
        printf("cmd handler 初始化失败\n");
        SYSTEM_PAUSE;
        return 0;
    }

    cmdResult = cmdHandler.HandleCommand(&cmdParam);
    if (cmdResult != S_OK)
    {
        printf("cmd handler 执行命令接口调用失败\n");
        cmdHandler.Finish();
        SYSTEM_PAUSE;
        return 0;
    }

    system("pause");
    return 0;
}