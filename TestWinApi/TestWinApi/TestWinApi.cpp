// TestWinApi.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "FileIO.h"
#include "NetUtil.h"
#include <iostream>
#include <list>
#include "FileUtil.h"

int _tmain(int argc, _TCHAR* argv[])
{
    //DirectoryCheck();

    /*std::list<std::string> ipList;
    if (GetAllLocalIP(ipList))
    {
        for (std::string& ip : ipList)
        {
            std::cout << ip.c_str() << std::endl;
        }
    }*/

    std::string fpath = "";
    std::string subpath = "\\test";
    FileUtil::PathJoin(fpath, subpath);

    system("pause");
	return 0;
}

