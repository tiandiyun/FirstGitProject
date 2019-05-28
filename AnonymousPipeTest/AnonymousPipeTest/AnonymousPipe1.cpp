#include "stdafx.h"
#include "AnonymousPipe1.h"
#include "windows.h"
#include "iostream"

using namespace std;

int CommunicatWithAnonymousPipe()
{
    PROCESS_INFORMATION pi;
    SECURITY_ATTRIBUTES sa;
    HANDLE hOutPut, hInPut;
    DWORD readByte = 0;
    int len = 0;
    BOOL hResult;
    char buffer[4096];

    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.bInheritHandle = TRUE;
    sa.lpSecurityDescriptor = NULL;

    if (!CreatePipe(&hOutPut, &hInPut, &sa, 0))
    {
        cout << "create pipe failed erorr=" << GetLastError() << endl;
        return 1;
    }

    STARTUPINFO st;
    st.cb = sizeof(STARTUPINFO);
    GetStartupInfo(&st);

    st.hStdOutput = hInPut;
    st.hStdError = hInPut;
    st.wShowWindow = SW_HIDE;
    st.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

    //     if (!CreateProcess(NULL, "c:\\windows\\system32\\cmd.exe /c ipconfig /all", NULL,
    //         NULL, TRUE, NULL, NULL, NULL, &st, &pi))
    if (!CreateProcess(NULL, "c:\\windows\\system32\\cmd.exe /c ping www.baidu.com", NULL,
        NULL, TRUE, NULL, NULL, NULL, &st, &pi))
    {
        cout << "failed create proccess,error=" << GetLastError() << endl;
        return 1;
    }

    DWORD dwRet = WaitForSingleObject(pi.hProcess, INFINITE);
    switch (dwRet)
    {
    case WAIT_TIMEOUT:
    case WAIT_FAILED:
        return 1;
    case WAIT_OBJECT_0:
        CloseHandle(hInPut);    //close hInPut handle ,make hte write pipe completes
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }

    memset(buffer, 0, sizeof(buffer));
    do
    {
        //a write operation completes on the write end of the pipe,so ReadFile can begin
        hResult = ReadFile(hOutPut, buffer + len, 1024, &readByte, NULL);
        len += readByte;
        Sleep(200);
    } while (readByte != 0 && hResult);

    cout << buffer << endl;

    CloseHandle(hOutPut);
    system("pause");
    return 0;
}


int CommunicatWithTmpFile()
{
    HANDLE hFile;
    STARTUPINFO st = { sizeof(STARTUPINFO) };
    PROCESS_INFORMATION pi;
    char szTempPath[MAX_PATH];
    char szTempFile[MAX_PATH];
    char buffer[4096];
    char cmdLine[512];
    DWORD dwRet;
    DWORD dwReadByte;

    dwRet = GetTempPath(MAX_PATH, szTempPath);
    if (!SUCCEEDED(dwRet))
    {
        cout << "failed to Get temp path" << GetLastError() << endl;
        return 1;
    }

    dwRet = GetTempFileName(szTempPath, TEXT("JJJJJay.txt"), 0, szTempFile);
    if (!SUCCEEDED(dwRet))
    {
        cout << "failed to create temp file" << GetLastError() << endl;
        return 1;
    }

    memset(cmdLine, 0, sizeof(cmdLine));
    int strLen = sizeof("c:\\windows\\system32\\cmd.exe /c ipconfig /all >");
    memcpy(cmdLine, "c:\\windows\\system32\\cmd.exe /c ipconfig /all >", strLen);
    memcpy(cmdLine + strLen - 1, szTempFile, sizeof(szTempFile));
    cmdLine[strLen + sizeof(szTempFile)] = '\0';
    cout << cmdLine << endl;

    if (!CreateProcess(NULL, cmdLine, NULL, NULL, TRUE, NULL, NULL, NULL, &st, &pi))
    {
        cout << "failed create proccess,error=" << GetLastError() << endl;
        return 1;
    }

    dwRet = WaitForSingleObject(pi.hProcess, INFINITE);
    switch (dwRet)
    {
    case WAIT_TIMEOUT:
    case WAIT_FAILED:
        return 1;
    case WAIT_OBJECT_0:
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }

    hFile = CreateFile(szTempFile, GENERIC_READ, FILE_SHARE_DELETE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        cout << "failed to create file" << GetLastError() << endl;
        return 0;
    }

    memset(buffer, 0, sizeof(buffer));
    int len = 0;
    do
    {
        dwRet = ReadFile(hFile, buffer + len, 1024, &dwReadByte, NULL);
        len += dwReadByte;
    } while (dwRet && dwReadByte != 0);

    cout << buffer << std::endl;

    CloseHandle(hFile);
    DeleteFile(szTempFile);

    system("pause");
    return 0;
}