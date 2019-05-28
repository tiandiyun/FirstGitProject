// TestSingleEvent.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


#include <windows.h>  
#include <iostream>  
using namespace std;

DWORD WINAPI ThreadProc(LPVOID lpParam);
DWORD WINAPI ThreadProc2(LPVOID lpParam);

DWORD g_dwThreadID;
DWORD g_dwThreadID2;

UINT g_nTickets = 300;
HANDLE g_hEvent = NULL;

DWORD WINAPI ThreadProc(LPVOID lpParam)
{
    // cout << "No." << g_dwThreadID << " thread is running." << endl;  
    while (TRUE)
    {
        auto res = WaitForSingleObject(g_hEvent, INFINITE);
        if (g_nTickets > 0)
        {
            Sleep(1);
            cout << "No.1-" << g_dwThreadID << " sell ticket : " << g_nTickets << endl;
            g_nTickets--;
            SetEvent(g_hEvent);
        }
        else
        {
            break;
        }
    }
    return 0;
}

DWORD WINAPI ThreadProc2(LPVOID lpParam)
{
    // cout << "No." << g_dwThreadID2 << " thread is running." << endl;  
    while (TRUE)
    {
        auto res = WaitForSingleObject(g_hEvent, INFINITE);
        if (g_nTickets > 0)
        {
            Sleep(1);
            cout << "No.2-" << g_dwThreadID2 << " sell ticket : " << g_nTickets << endl;
            g_nTickets--;
            SetEvent(g_hEvent);
        }
        else
        {
            break;
        }
    }
    return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
    cout << "Main thread is running." << endl;

    /*HANDLE hHandle = CreateThread(NULL, 0, ThreadProc, NULL, 0, &g_dwThreadID);
    HANDLE hHandle2 = CreateThread(NULL, 0, ThreadProc2, NULL, 0, &g_dwThreadID2);
    CloseHandle(hHandle);
    CloseHandle(hHandle2);*/

    g_hEvent = CreateEvent(NULL, FALSE, TRUE, NULL);

    while (1)
    {
        auto res = WaitForSingleObject(g_hEvent, INFINITE); //WAIT_OBJECT_0
        cout << res << endl; 
        ResetEvent(g_hEvent);
    }

    Sleep(4000);
    system("pause");
    return 0;
}

