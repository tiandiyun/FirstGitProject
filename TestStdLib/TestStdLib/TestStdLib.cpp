// TestStdLib.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <list>

using namespace std;

void TestDiv()
{
    div_t dv = div(5, 3);
    cout << "div(5, 3) -- quot: " << dv.quot << ", rem: " << dv.rem << endl;

    dv = div(4, 2);
    cout << "div(4, 2) -- quot: " << dv.quot << ", rem: " << dv.rem << endl;
}

void TestS2D()
{
	std::list<long> numList;
	char* srcStr = "    590be123ar";
	char* next = srcStr;
	while (next && *next)
	{
		char* tmpNext = nullptr;
		long num = strtol(next, &tmpNext, 10);
		if (next != tmpNext)
		{
			numList.push_back(num);
			next = tmpNext;
		}
		else
		{
			++next;
		}
	}
}

#define TOSTR(X) #X
#define JOIN(X) pre##X
#define DEF(X) static int INT##X = 0

void TestHash()
{
	int prex = 0;
	std::cout << TOSTR(x + y + z) << std::endl;
	std::cout << JOIN(x) << std::endl;
	DEF(_A);
	std::cout << INT_A << std::endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	TestHash();

    system("pause");
	return 0;
}

