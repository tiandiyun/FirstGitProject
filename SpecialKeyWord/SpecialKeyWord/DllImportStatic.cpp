#include "stdafx.h"
#include "DllImportStatic.h"
#include <Windows.h>
#include <iostream>
#include "E:\\Project\\Test\\FirstGitProject\\DllExport\\DllExport\\Export.h"

#pragma comment(lib, "E:\\Project\\Test\\FirstGitProject\\DllExport\\Debug\\DllExport.lib")


void StaticLoadExternDll()
{
    char path[MAX_PATH] = { 0 };
    GetCurrentDirectory(sizeof(path), path);

    std::cout << "CExpData: " << CExpData << std::endl;

    std::cout << "CAddCdecl: ";
    std::cout << CAddCdecl(1, 2) << std::endl;

    std::cout << "CAddStdCall: ";
    std::cout << CAddStdCall(1, 2) << std::endl;

    std::cout << "CAddFastCall: ";
    std::cout << CAddFastCall(1, 2) << std::endl;


    std::cout << "CppExpData: " << CppExpData << std::endl;

    std::cout << "CppAddCdecl: ";
    std::cout << CppAddCdecl(1, 2) << std::endl;

    std::cout << "CppAddStdCall: ";
    std::cout << CppAddStdCall(1, 2) << std::endl;

    std::cout << "CppAddFastCall: ";
    std::cout << CppAddFastCall(1, 2) << std::endl;
}

