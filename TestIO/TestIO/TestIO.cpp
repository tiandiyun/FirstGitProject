// TestIO.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>

void TestGetC()
{
    char ch;
    printf("Input a character: ");   //输入提示信息
    ch = fgetc(stdin);  // 从标准输入控制台中读取字符
    printf("The character input was: '%c'\n", ch);  // 输出字符
}

int _tmain(int argc, _TCHAR* argv[])
{
    TestGetC();

    system("pause");
	return 0;
}

