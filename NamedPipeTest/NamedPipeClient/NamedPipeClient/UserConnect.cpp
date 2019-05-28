#include "stdafx.h"

// Need to link with Netapi32.lib and Mpr.lib
#pragma comment(lib, "mpr.lib")

#include <tchar.h>
#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <Winnetwk.h>
#include "UserConnect.h"

using namespace std;

#define BUFSIZE 512

OneOffConnection::OneOffConnection(const char* serverPath, const char* user, const char* password, const char* localName)
{
    mServerName = serverPath;
    mConnectFlag = ConnectServer(user, password, localName);
}

OneOffConnection::~OneOffConnection()
{
    if (mConnectFlag && DisconnectServer())
    {
        mConnectFlag = false;
    }
}

bool OneOffConnection::ConnectServer(const char* user, const char* password, const char* localName)
{
    DisconnectServer();

    //
    // Assign values to the NETRESOURCE structure.
    //

    LPTSTR lpStr = NULL;
    string tmpStr;
    if (localName != NULL)
    {
        tmpStr = localName;
        lpStr = TEXT(&(tmpStr[0]));
    }

    NETRESOURCE nr;
    //nr.dwDisplayType = RESOURCEDISPLAYTYPE_DIRECTORY;
    nr.dwType = RESOURCETYPE_ANY;
    nr.dwScope = RESOURCE_GLOBALNET;
    nr.dwUsage = 0;
    nr.lpComment = TEXT("");
    nr.lpLocalName = lpStr;
    nr.lpRemoteName = TEXT(&(mServerName[0]));
    nr.lpProvider = NULL;

    //
    // Call the WNetAddConnection2 function to assign
    //   a drive letter to the share.
    //
    DWORD dwFlags = CONNECT_UPDATE_PROFILE;
    DWORD res = WNetAddConnection2(&nr, password, user, dwFlags);

    //
    // If the call succeeds, inform the user; otherwise,
    //  print the error.
    //
    if (res != NO_ERROR)
    {
        cout << "Error: " << res << endl;
        return false;
    }

    cout << "Connection success" << endl;
    return true;
}

bool OneOffConnection::DisconnectServer()
{
    return NO_ERROR == WNetCancelConnection2(mServerName.c_str(), 0, true);
}

bool OneOffConnection::IsConnected()
{
    return mConnectFlag;
}



AutoReleasePipe::AutoReleasePipe(const char* serverPath, const char* pipName)
{
    string pipeName = serverPath;
    pipeName += "\\pipe\\";
    pipeName += pipName;
    CreatePipe(pipeName);
}

AutoReleasePipe::~AutoReleasePipe()
{
    DestoryPipe();
}

bool AutoReleasePipe::CreatePipe(string& pipeName)
{
    LPTSTR lpszPipename = TEXT(&(pipeName[0]));

    int retryCount = 10;
    while (retryCount-- > 0)
    {
        mPipeHanle = CreateFile(
            lpszPipename,                   // pipe name   
            GENERIC_READ | GENERIC_WRITE,   // read and write access   
            0,                              // no sharing   
            NULL,                           // default security attributes  
            OPEN_EXISTING,                  // opens existing pipe   
            //0,                              // default attributes   
            FILE_FLAG_OVERLAPPED,
            NULL);                          // no template file   

        // Break if the pipe handle is valid.   
        if (mPipeHanle != INVALID_HANDLE_VALUE)
        {
            break;
        }

        // Exit if an error other than ERROR_PIPE_BUSY occurs.   
        if (GetLastError() != ERROR_PIPE_BUSY)
        {
            printf("Could not open pipe");
            return false;
        }

        // All pipe instances are busy, so wait for 20 seconds.   
        if (!WaitNamedPipe(lpszPipename, 20000))
        {
            printf("Could not open pipe");
            return false;
        }
    }

    if (mPipeHanle == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    DWORD dwMode = PIPE_READMODE_MESSAGE;
    BOOL fSuccess = SetNamedPipeHandleState(
        mPipeHanle,     // pipe handle   
        &dwMode,        // new pipe mode   
        NULL,           // don't set maximum bytes   
        NULL);          // don't set maximum time   

    if (fSuccess != TRUE)
    {
        printf("SetNamedPipeHandleState failed");
        DestoryPipe();
        return false;
    }

    return true;
}

void AutoReleasePipe::DestoryPipe()
{
    if (IsConnected())
    {
        CloseHandle(mPipeHanle);
        mPipeHanle = INVALID_HANDLE_VALUE;
    }
}

bool AutoReleasePipe::IsConnected()
{
    return mPipeHanle != INVALID_HANDLE_VALUE;
}

bool AutoReleasePipe::ReadFileWithEvent()
{
    OVERLAPPED ol;
    ZeroMemory(&ol, sizeof(ol));

    ol.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

    DWORD readLen = 0;
    TCHAR readBuffer[BUFSIZE] = { 0 };
    BOOL fSuccess = ReadFile(
        mPipeHanle,                     // pipe handle   
        readBuffer,                     // buffer to receive reply   
        BUFSIZE * sizeof(TCHAR),        // size of buffer   
        &readLen,                       // number of bytes read   
        &ol);                           // not overlapped

    if (fSuccess == FALSE)
    {
        if (GetLastError() == ERROR_IO_PENDING)
        {
            DWORD waitRes = WaitForSingleObject(ol.hEvent, INFINITE);
            if (WAIT_OBJECT_0 == waitRes)
            {
                readLen = 0;
                ZeroMemory(readBuffer, sizeof(readBuffer));
                ZeroMemory(&ol, sizeof(ol));
                
                BOOL fSuccess = ReadFile(
                    mPipeHanle,                     // pipe handle   
                    readBuffer,                     // buffer to receive reply   
                    BUFSIZE * sizeof(TCHAR),        // size of buffer   
                    &readLen,                       // number of bytes read   
                    NULL);                          // not overlapped
            }
        }
    }
    return true;
}

void AutoReleasePipe::CommunicateMsg()
{
    if (!IsConnected())
    {
        return;
    }

    string msg;
    while (true)
    {
        msg.clear();
        getline(std::cin, msg);
        LPTSTR lpvMessage = TEXT(&(msg[0]));

        DWORD writeLen = 0;
        BOOL fSuccess = WriteFile(
            mPipeHanle,                                 // pipe handle   
            lpvMessage,                                 // message   
            (lstrlen(lpvMessage) + 1) * sizeof(TCHAR),  // message length   
            &writeLen,                                  // bytes written   
            NULL);                                      // not overlapped   
        if (!fSuccess)
        {
            printf("WriteFile failed");
            break;
        }

        ReadFileWithEvent();
        continue;

        // Read from the pipe. 
        DWORD readLen = 0;
        TCHAR readBuffer[BUFSIZE] = { 0 };
        ZeroMemory(readBuffer, sizeof(readBuffer));
        fSuccess = ReadFile(
            mPipeHanle,                     // pipe handle   
            readBuffer,                     // buffer to receive reply   
            BUFSIZE * sizeof(TCHAR),        // size of buffer   
            &readLen,                       // number of bytes read   
            NULL);                          // not overlapped   

        if (!fSuccess && GetLastError() != ERROR_MORE_DATA)
        {
            break;  // repeat loop if ERROR_MORE_DATA
        }

        //_tprintf(TEXT("%s\n"), chBuf);
        cout << "Server: " << readBuffer << endl;
    }
}
