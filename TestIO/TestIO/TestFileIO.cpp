#include "stdafx.h"
#include "TestFileIO.h"
#include <iostream>
#include <windows.h>
#include <fstream>

void TestCPPOpenFile()
{
    using namespace std;

    // TODO: tianyun ���Դ���
    char path[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, path);

    string patchStr{ path };
    patchStr += "\\testio.txt";
    cout << patchStr.c_str() << endl;

    ofstream ofile;       //��������ļ�
    ofile.open(patchStr, ios::out/*ios::app*/);     //��Ϊ����ļ���
    ofile.flags(ios::left);
    ofile << "========" << endl;
    ofile.close();
}