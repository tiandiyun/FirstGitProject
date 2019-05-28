#include "stdafx.h"
#include "TestFileIO.h"
#include <iostream>
#include <windows.h>
#include <fstream>

void TestCPPOpenFile()
{
    using namespace std;

    // TODO: tianyun 测试代码
    char path[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, path);

    string patchStr{ path };
    patchStr += "\\testio.txt";
    cout << patchStr.c_str() << endl;

    ofstream ofile;       //定义输出文件
    ofile.open(patchStr, ios::out/*ios::app*/);     //作为输出文件打开
    ofile.flags(ios::left);
    ofile << "========" << endl;
    ofile.close();
}