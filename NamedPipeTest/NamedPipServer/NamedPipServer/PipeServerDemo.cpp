/*!
*
*
服务端代码流程：

1、创建命名管道：CreateNamedPipe

2、等待客户端连接：ConnectNamedPipe

3、读取客户端请求数据：ReadFile

4、向客户端回复数据：WriteFile

5、关闭连接：DisconnectNamedPipe

6、关闭管道：CloseHandle
*
* \author Administrator
* \date 四月 2019
*/

#include "stdafx.h"
#include <iostream>
#include <windows.h>  
#include <strsafe.h> 


#define BUFSIZE 4096  


VOID GetAnswerToRequest(LPTSTR chRequest, LPTSTR chReply, LPDWORD pchBytes)
{
    std::cout << chRequest << std::endl;

    _tprintf(TEXT("%s\n"), chRequest);
    StringCchCopy(chReply, BUFSIZE, TEXT("Default answer from server"));
    *pchBytes = (lstrlen(chReply) + 1) * sizeof(TCHAR);
}


DWORD WINAPI InstanceThread(LPVOID lpvParam)
{
    // The thread's parameter is a handle to a pipe instance.   

    TCHAR chRequest[BUFSIZE] = { 0 };
    TCHAR chReply[BUFSIZE] = { 0 };
    DWORD cbBytesRead = 0;
    DWORD cbReplyBytes = 0;
    DWORD cbWritten = 0;
    BOOL fSuccess = FALSE;
    HANDLE hPipe = (HANDLE)lpvParam;

    while (1)
    {
        // Read client requests from the pipe.
        cbBytesRead = 0;
        ZeroMemory(chRequest, sizeof(chRequest));
        fSuccess = ReadFile(
            hPipe,        // handle to pipe   
            chRequest,    // buffer to receive data   
            BUFSIZE * sizeof(TCHAR), // size of buffer   
            &cbBytesRead, // number of bytes read   
            NULL);        // not overlapped I/O   

        if (!fSuccess || cbBytesRead == 0)
            break;

        GetAnswerToRequest(chRequest, chReply, &cbReplyBytes);

        // Write the reply to the pipe.   
        fSuccess = WriteFile(
            hPipe,        // handle to pipe   
            chReply,      // buffer to write from   
            cbReplyBytes, // number of bytes to write   
            &cbWritten,   // number of bytes written   
            NULL);        // not overlapped I/O   

        if (!fSuccess || cbReplyBytes != cbWritten)
            break;
    }

    // Flush the pipe to allow the client to read the pipe's contents   
    // before disconnecting. Then disconnect the pipe, and close the   
    // handle to this pipe instance.   
    FlushFileBuffers(hPipe);
    DisconnectNamedPipe(hPipe);
    CloseHandle(hPipe);

    return 1;
}


int TestPipeServer()
{
    BOOL fConnected;
    DWORD dwThreadId;
    HANDLE hPipe, hThread;
    //LPTSTR lpszPipename = TEXT("\\\\.\\pipe\\mynamedpipe");
    LPTSTR lpszPipename = TEXT("\\\\.\\pipe\\FishingPipe");

    // The main loop creates an instance of the named pipe and   
    // then waits for a client to connect to it. When the client   
    // connects, a thread is created to handle communications   
    // with that client, and the loop is repeated.   
    for (;;)
    {
        hPipe = CreateNamedPipe(
            lpszPipename,               // pipe name   
            PIPE_ACCESS_DUPLEX,         // read/write access   
            PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,  // message type pipe | message-read mode | blocking mode
            PIPE_UNLIMITED_INSTANCES,   // max. instances    
            BUFSIZE,                    // output buffer size   
            BUFSIZE,                    // input buffer size   
            0,                          // client time-out   
            NULL);                      // default security attribute   

        if (hPipe == INVALID_HANDLE_VALUE)
        {
            printf("CreatePipe failed");
            return 0;
        }

        // Wait for the client to connect; if it succeeds,   
        // the function returns a nonzero value. If the function  
        // returns zero, GetLastError returns ERROR_PIPE_CONNECTED.   

        fConnected = ConnectNamedPipe(hPipe, NULL) ? TRUE : (GetLastError() == ERROR_PIPE_CONNECTED);
        if (fConnected)
        {
            // Create a thread for this client.   
            hThread = CreateThread(
                NULL,              // no security attribute   
                0,                 // default stack size   
                InstanceThread,    // thread proc  
                (LPVOID)hPipe,     // thread parameter   
                0,                 // not suspended   
                &dwThreadId);      // returns thread ID   

            if (hThread == NULL)
            {
                printf("CreateThread failed");
                CloseHandle(hPipe);
                return 0;
            }
            else
            {
                CloseHandle(hThread);
            }
        }
        else
        {
            // The client could not connect, so close the pipe.   
            CloseHandle(hPipe);
        }
    }

    return 0;
}

