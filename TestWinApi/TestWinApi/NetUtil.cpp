#include "stdafx.h"
#include "NetUtil.h"

#ifdef WIN32
#include <windows.h>
#include <winsock.h>
#include <stdio.h>
#pragma comment(lib, "ws2_32.lib") //用于链接到ws2_32.lib这个库
#endif


#define DEFAULT_IP "127.0.0.1"
#define MAX_PATH 260

// 获得本机的IP地址
bool GetAllLocalIP(list<string> &ipList)
{
    //装载winsock库
    WORD wVersionRequested = MAKEWORD(1, 1);
    WSADATA wsaData;
    if (WSAStartup(wVersionRequested, &wsaData) != 0)
    {
        return false;
    }

    // 获得本机主机名
    char hostname[MAX_PATH] = { 0 };
    gethostname(hostname, MAX_PATH);
    struct hostent FAR* lpHostEnt = gethostbyname(hostname); 
    if (lpHostEnt == nullptr)
    {
        ipList.emplace_back(string(DEFAULT_IP));
        return true;
    }

    //如果获得主机名成功的话，调用inet_ntoa()函数取得IP地址
    LPSTR* lpAddr = lpHostEnt->h_addr_list;
    if (!lpAddr)
    {
        return false;
    }

    while (*lpAddr != nullptr)
    {
        const char* szIP = ::inet_ntoa(*(in_addr *)*lpAddr);
        ipList.emplace_back(string(szIP));
        ++lpAddr;
    }

    return true;
}