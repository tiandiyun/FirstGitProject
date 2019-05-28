#include "stdafx.h"
#include "DllImportDynamic.h"
#include <Windows.h>
#include <iostream>


void DynamicLoadExternDll()
{
    using addCdecl = int(__cdecl*)(int, int);
    using addStdCall = int(__stdcall*)(int, int);
    using addFastCall = int(__fastcall*)(int, int);

    HINSTANCE hInst = LoadLibraryA("E:\\Project\\Test\\FirstGitProject\\DllExport\\Debug\\DllExport.dll");

    int cExp = *(int*)GetProcAddress(hInst, "CExpData");
    std::cout << "CExpData: " << cExp << std::endl;

    addCdecl addc = (addCdecl)GetProcAddress(hInst, "CAddCdecl");
    std::cout << "CAddCdecl: ";
    std::cout << addc(1, 2) << std::endl;

    addStdCall adds = (addStdCall)GetProcAddress(hInst, "CAddStdCall");
    std::cout << "CAddStdCall: ";
    std::cout << adds(1, 2) << std::endl;

    addFastCall addf = (addFastCall)GetProcAddress(hInst, "CAddFastCall");
    std::cout << "CAddFastCall: ";
    std::cout << addf(1, 2) << std::endl;


    int cppExp = *(int*)GetProcAddress(hInst, "CppExpData");
    std::cout << "CppExpData: " << cppExp << std::endl;

    addc = (addCdecl)GetProcAddress(hInst, "CppAddCdecl");
    std::cout << "CppAddCdecl: ";
    std::cout << addc(1, 2) << std::endl;

    adds = (addStdCall)GetProcAddress(hInst, "CppAddStdCall");
    std::cout << "CppAddStdCall: ";
    std::cout << adds(1, 2) << std::endl;

    addf = (addFastCall)GetProcAddress(hInst, "CppAddFastCall");
    std::cout << "CppAddFastCall: ";
    std::cout << addf(1, 2) << std::endl;
}

