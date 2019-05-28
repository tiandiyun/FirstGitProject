// SpecialKeyWord.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
// #include "DllImportDynamic.h"
//#include "DllImportStatic.h"
#include "CallStaticLib.h"


#pragma  message("~~~~~~This is customized compile message~~~~~~~")  
#ifdef _WIN32
#pragma  message("~~~~~~_WIN32 is defined~~~~~~~")  
#endif


#define LIBPATH(p,f)   p##f 
#define CurrLib LIBPATH(__FILE__, "..\\srilm-lib\\common.lib")



int _tmain(int argc, _TCHAR* argv[])
{
    //DynamicLoadExternDll();
    //StaticLoadExternDll();
    CallStaticLib();
    system("pause");
	return 0;
}

