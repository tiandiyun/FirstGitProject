// TestIO.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stdlib.h>

void TestGetC()
{
    char ch;
    printf("Input a character: ");   //������ʾ��Ϣ
    ch = fgetc(stdin);  // �ӱ�׼�������̨�ж�ȡ�ַ�
    printf("The character input was: '%c'\n", ch);  // ����ַ�
}

int _tmain(int argc, _TCHAR* argv[])
{
    TestGetC();

    system("pause");
	return 0;
}

