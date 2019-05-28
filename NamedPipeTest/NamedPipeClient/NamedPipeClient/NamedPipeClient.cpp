/*!
*
*
客户端代码流程：

1、打开命名管道：CreateFile

2、等待服务端响应：WaitNamedPipe

3、切换管道为读模式：SetNamedPipeHandleState

4、向服务端发数据：WriteFile

5、读服务端返回的数据：ReadFile

6、关闭管道：CloseHandle
*
* \author Administrator
* \date 四月 2019
*/

#include "stdafx.h"
#include <iostream>
#include <windows.h>  
#include "UserConnect.h"

#define BUFSIZE 512  

//#define _REMOTE

#ifdef _REMOTE

#   define __PTH   "\\\\10.1.3.98\\upshare"
#   define __USR   "Administrator"
#   define __PWD   "Dgl19830805"
#   define __LOCALNAME   "Z:"

#else

// #   define __PTH   "\\\\127.0.0.1\\upshare"
// #   define __USR   "Administrator"
// #   define __PWD   "*Tian123"
// #   define __LOCALNAME   "Z:"

#   define __PTH   "\\\\127.0.0.1"
#   define __USR   "Administrator"
#   define __PWD   "*Tian123"
#   define __LOCALNAME   NULL

#endif

//#define _PIPENAME   "FishingPipe"
#define _PIPENAME   "PipeCtrlServer"

using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
    OneOffConnection conn(__PTH, __USR, __PWD, __LOCALNAME);
    if (!conn.IsConnected())
    {
        cout << "Logon server failed" << endl;
        return -1;
    }

    AutoReleasePipe arPipe(__PTH, _PIPENAME);
    if (arPipe.IsConnected())
    {
        arPipe.CommunicateMsg();
    }
    
    system("pause");
    return 0;

    HANDLE hPipe;
    LPTSTR lpvMessage = TEXT("Default message from client");
    TCHAR chBuf[BUFSIZE];
    BOOL fSuccess;
    DWORD cbRead, cbWritten, dwMode;
    //LPTSTR lpszPipename = TEXT("\\\\.\\pipe\\mynamedpipe"); // \\.\pipe\mynamedpipe
    LPTSTR lpszPipename = TEXT(__PTH "\\pipe\\FishingShutDownPipe");

    if (argc > 1)
        lpvMessage = argv[1];

    // Try to open a named pipe; wait for it, if necessary.   
    while (1)
    {
        hPipe = CreateFile(
            lpszPipename,                   // pipe name   
            GENERIC_READ | GENERIC_WRITE,   // read and write access   
            0,                              // no sharing   
            NULL,                           // default security attributes  
            OPEN_EXISTING,                  // opens existing pipe   
            0,                              // default attributes   
            NULL);                          // no template file   

        // Break if the pipe handle is valid.   
        if (hPipe != INVALID_HANDLE_VALUE)
            break;

        // Exit if an error other than ERROR_PIPE_BUSY occurs.   
        if (GetLastError() != ERROR_PIPE_BUSY)
        {
            printf("Could not open pipe");
            return 0;
        }

        // All pipe instances are busy, so wait for 20 seconds.   
        if (!WaitNamedPipe(lpszPipename, 20000))
        {
            printf("Could not open pipe");
            return 0;
        }
    }

    // The pipe connected; change to message-read mode.   
    dwMode = PIPE_READMODE_MESSAGE;
    fSuccess = SetNamedPipeHandleState(
        hPipe,    // pipe handle   
        &dwMode,  // new pipe mode   
        NULL,     // don't set maximum bytes   
        NULL);    // don't set maximum time   
    if (!fSuccess)
    {
        printf("SetNamedPipeHandleState failed");
        CloseHandle(hPipe);
        return 0;
    } 


    string msg;
    while (true)
    {
        getline(std::cin, msg);
        lpvMessage = TEXT(&(msg[0]));

        fSuccess = WriteFile(
            hPipe,                                      // pipe handle   
            lpvMessage,                                 // message   
            (lstrlen(lpvMessage) + 1) * sizeof(TCHAR),  // message length   
            &cbWritten,                                 // bytes written   
            NULL);                                      // not overlapped   
        if (!fSuccess)
        {
            printf("WriteFile failed");
            break;
        }

        // Read from the pipe.   
        fSuccess = ReadFile(
            hPipe,                      // pipe handle   
            chBuf,                      // buffer to receive reply   
            BUFSIZE * sizeof(TCHAR),    // size of buffer   
            &cbRead,                    // number of bytes read   
            NULL);                      // not overlapped   

        if (!fSuccess && GetLastError() != ERROR_MORE_DATA)
        {
            break;  // repeat loop if ERROR_MORE_DATA
        }

        //_tprintf(TEXT("%s\n"), chBuf);
        cout << chBuf << endl;
    }

    return 0;

    CloseHandle(hPipe);

    system("pause");
    return 0;
}

