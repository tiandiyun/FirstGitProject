// TestWinApi.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "FileIO.h"
#include "NetUtil.h"
#include <iostream>
#include <list>


int _tmain(int argc, _TCHAR* argv[])
{
    //DirectoryCheck();

    std::list<std::string> ipList;
    if (GetAllLocalIP(ipList))
    {
        for (std::string& ip : ipList)
        {
            std::cout << ip.c_str() << std::endl;
        }
    }

    system("pause");
	return 0;
}

