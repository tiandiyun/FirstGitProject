#pragma once

#include <string>
#include <wtypes.h>

class OneOffConnection
{
public:
    OneOffConnection(const char* serverPath, const char* user, const char* password, const char* localName);

    ~OneOffConnection();

    bool    IsConnected();

    bool    DisconnectServer();

protected:
    OneOffConnection() = default;
    OneOffConnection(const OneOffConnection&) = delete;
    OneOffConnection& operator=(const OneOffConnection&) = delete;

private:
    bool ConnectServer(const char* user, const char* password, const char* localName);

private:
    std::string mServerName;
    bool        mConnectFlag{ false };
};



class AutoReleasePipe
{
public:
    AutoReleasePipe(const char* serverPath, const char* pipName);

    ~AutoReleasePipe();

    bool    IsConnected();

    bool    ReadFileWithEvent();

    void    CommunicateMsg();

protected:
    AutoReleasePipe() = default;
    AutoReleasePipe(const AutoReleasePipe&) = delete;
    AutoReleasePipe& operator=(const AutoReleasePipe&) = delete;

private:
    bool    CreatePipe(std::string& pipeName);

    void    DestoryPipe();

private:
    HANDLE mPipeHanle{ INVALID_HANDLE_VALUE };
};