// TestIO.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdarg.h>
#include "TestFileIO.h"

void TestGetC()
{
    char ch;
    printf("Input a character: ");   //输入提示信息
    ch = fgetc(stdin);  // 从标准输入控制台中读取字符
    printf("The character input was: '%c'\n", ch);  // 输出字符
}

void TestScanf()
{
	char buf[512] = { 0 };
	sscanf_s("hello, world", "%*s%s", buf, sizeof(buf) - 1);
	printf("%s\n", buf);

	char sztime1[16] = "", sztime2[16] = "";
	sscanf_s("2006:03:18  -   2006:04:18", "%s - %s", sztime1, sizeof(sztime1) - 1, sztime2, sizeof(sztime2) - 1);
}

void Log(const char * szFormat, ...)
{
    char buff[256] = { 0 };
    va_list args;
    va_start(args, szFormat);
    vsprintf_s(buff, sizeof(buff), szFormat, args);
    va_end(args);
}

int _tmain(int argc, _TCHAR* argv[])
{
    //TestGetC();

    TestCPPOpenFile();

    system("pause");
	return 0;
}

