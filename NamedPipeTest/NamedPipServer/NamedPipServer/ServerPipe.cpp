#include "stdafx.h"
#include "ServerPipe.h"
#include <iostream>
#include <tchar.h>
#include <stdio.h>
#include <windows.h>
#include <thread>

using namespace std;

#define BUFSIZE 4096

ServerPipe::ServerPipe(const char* serverPath, const char* pipName)
{
    string pipeName = serverPath;
    pipeName += "\\pipe\\";
    pipeName += pipName;
    CreatePipe(pipeName);
}

ServerPipe::~ServerPipe()
{
    DestoryPipe();
}

bool ServerPipe::CreatePipe(std::string& pipeName)
{
    LPTSTR lpszPipename = TEXT(&(pipeName[0]));

    mPipeHanle = CreateNamedPipe(
        lpszPipename,               // pipe name   
        PIPE_ACCESS_DUPLEX,         // read/write access   
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,  // message type pipe | message-read mode | blocking mode
        PIPE_UNLIMITED_INSTANCES,   // max. instances    
        BUFSIZE,                    // output buffer size   
        BUFSIZE,                    // input buffer size   
        0,                          // client time-out   
        NULL);                      // default security attribute   

    if (mPipeHanle == INVALID_HANDLE_VALUE)
    {
        cout << "Create pipe failed" << endl;
        return false;
    }

    cout << "Create pipe success" << endl;
    return true;
}

void ServerPipe::DestoryPipe()
{
    DisconnectPipe();

    if (mPipeHanle != INVALID_HANDLE_VALUE)
    {
        CloseHandle(mPipeHanle);
        mPipeHanle = INVALID_HANDLE_VALUE;
    }
}

bool ServerPipe::ConnectPipe()
{
    // Wait for the client to connect; if it succeeds,   
    // the function returns a nonzero value. If the function  
    // returns zero, GetLastError returns ERROR_PIPE_CONNECTED.   
    if (ConnectNamedPipe(mPipeHanle, NULL) || GetLastError() != ERROR_PIPE_CONNECTED)
    {
        SetConnectedFlag(true);
    }
    else
    {
        SetConnectedFlag(false);
    }

    return IsConnected();
}

void ServerPipe::DisconnectPipe()
{
    if (IsConnected())
    {
        // Flush the pipe to allow the client to read the pipe's contents   
        // before disconnecting. Then disconnect the pipe, and close the   
        // handle to this pipe instance.   
        FlushFileBuffers(mPipeHanle);
        DisconnectNamedPipe(mPipeHanle);
        SetConnectedFlag(false);
    }
}

bool ServerPipe::IsConnected()
{
    return mConnectedFlag;
}

void ServerPipe::SetConnectedFlag(bool flag)
{
    mConnectedFlag = flag;
}

void ServerPipe::AcceptMessage()
{
    TCHAR requestBuffer[BUFSIZE] = { 0 };
    LPTSTR lpvMessage = nullptr;
    DWORD readLen = 0;
    DWORD writeLen = 0;
    DWORD writtenLen = 0;
    BOOL fSuccess = FALSE;
    string msg;
    while (1)
    {
        // Read client requests from the pipe.
        readLen = 0;
        ZeroMemory(requestBuffer, sizeof(requestBuffer));
        fSuccess = ReadFile(
            mPipeHanle,                 // handle to pipe   
            requestBuffer,              // buffer to receive data   
            BUFSIZE * sizeof(TCHAR),    // size of buffer   
            &readLen,                   // number of bytes read   
            NULL);                      // not overlapped I/O   

        if (!fSuccess || readLen == 0)
            break;
        cout << "Client: " << requestBuffer << endl;

        try
        {
            msg.clear();
            getline(std::cin, msg);
            lpvMessage = TEXT(&(msg[0]));
        }
        catch (std::exception &e)
        {
            cout << e.what() << endl;
        }

        // Write the reply to the pipe. 
        writeLen = (lstrlen(lpvMessage) + 1) * sizeof(TCHAR);
        fSuccess = WriteFile(
            mPipeHanle,                 // handle to pipe   
            lpvMessage,                 // buffer to write from   
            writeLen,                   // number of bytes to write   
            &writtenLen,                // number of bytes written   
            NULL);                      // not overlapped I/O   

        if (!fSuccess || writeLen != writtenLen)
            break;
    }

    DisconnectPipe();
    cout << "Disconnected." << endl << endl;
}

void ServerPipe::SyncListenPipe()
{
    cout << "Start to listen ..." << endl;

    while (1)
    {
        if (!ConnectPipe())
        {
            // The client could not connect, so close the pipe.   
            cout << "Connect pipe failed" << endl;
            DestoryPipe();
            break;
        }
        cout << "Connected." << endl;

        AcceptMessage();
    }

    DestoryPipe();
}

void ServerPipe::AsyncListenPipe()
{
    std::thread msgThread(&ServerPipe::SyncListenPipe, this);
    msgThread.join();
}