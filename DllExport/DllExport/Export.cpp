#include "stdafx.h"
#include "Export.h"
#include <iostream>

#pragma comment(linker, "/EXPORT:CAddStdCall=_CAddStdCall@8")
#pragma comment(linker, "/EXPORT:CAddFastCall=@CAddFastCall@8")

#pragma comment(linker, "/EXPORT:CppExpData=?CppExpData@@3HA")
#pragma comment(linker, "/EXPORT:CppAddCdecl=?CppAddCdecl@@YAHHH@Z")
#pragma comment(linker, "/EXPORT:CppAddStdCall=?CppAddStdCall@@YGHHH@Z")
#pragma comment(linker, "/EXPORT:CppAddFastCall=?CppAddFastCall@@YIHHH@Z")


int CExpData = 100;

static int CAdd(int a, int b)
{
    printf("%d+%d=", a, b);
    return a + b;
}

int __cdecl CAddCdecl(int a, int b)
{
    return CAdd(a, b);
}

int __stdcall CAddStdCall(int a, int b)
{
    return CAdd(a, b);
}

int __fastcall CAddFastCall(int a, int b)
{
    return CAdd(a, b);
}


int CppExpData = 200;

static int CppAdd(int a, int b)
{
    std::cout << a << "+" << b << "=";
    return a + b;
}

extern CALC_API int __cdecl CppAddCdecl(int a, int b)
{
    return CppAdd(a, b);
}

extern CALC_API int __stdcall CppAddStdCall(int a, int b)
{
    return CppAdd(a, b);
}

extern CALC_API int __fastcall CppAddFastCall(int a, int b)
{
    return CppAdd(a, b);
}
