#pragma once

#include <string>
#include <wtypes.h>

class ServerPipe
{
public:
    ServerPipe(const char* serverPath, const char* pipName);

    ~ServerPipe();

    bool    IsConnected();

    void    SetConnectedFlag(bool flag);

    void    SyncListenPipe();

    void    AsyncListenPipe();

protected:
    ServerPipe() = default;
    ServerPipe(const ServerPipe&) = delete;
    ServerPipe& operator=(const ServerPipe&) = delete;

private:
    bool    CreatePipe(std::string& pipeName);

    void    DestoryPipe();

    bool    ConnectPipe();

    void    DisconnectPipe();

    void    AcceptMessage();

private:
    HANDLE  mPipeHanle{ INVALID_HANDLE_VALUE };
    bool    mConnectedFlag{ false };
};