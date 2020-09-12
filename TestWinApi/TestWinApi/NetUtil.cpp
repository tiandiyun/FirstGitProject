#include "stdafx.h"
#include "NetUtil.h"

#ifdef WIN32
#include <windows.h>
#include <winsock.h>
#include <stdio.h>
#pragma comment(lib, "ws2_32.lib") //�������ӵ�ws2_32.lib�����
#endif


#define DEFAULT_IP "127.0.0.1"
#define MAX_PATH 260

// ��ñ�����IP��ַ
bool GetAllLocalIP(list<string> &ipList)
{
    //װ��winsock��
    WORD wVersionRequested = MAKEWORD(1, 1);
    WSADATA wsaData;
    if (WSAStartup(wVersionRequested, &wsaData) != 0)
    {
        return false;
    }

    // ��ñ���������
    char hostname[MAX_PATH] = { 0 };
    gethostname(hostname, MAX_PATH);
    struct hostent FAR* lpHostEnt = gethostbyname(hostname); 
    if (lpHostEnt == nullptr)
    {
        ipList.emplace_back(string(DEFAULT_IP));
        return true;
    }

    //�������������ɹ��Ļ�������inet_ntoa()����ȡ��IP��ַ
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