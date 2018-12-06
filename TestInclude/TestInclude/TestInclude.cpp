// TestInclude.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include "a.h"
#include "c.h"

void PrintB();

int _tmain(int argc, _TCHAR* argv[])
{
	/*printf("Before PrintC. a: %d\n", a);
	PrintC();
	printf("After PrintC. a: %d\n", a);

	++a;
	printf("now  a: %d\n", a);*/

    std::string str;
    std::string buf;

    //std::cin >> buf;

    str += buf;

    /*if (str.length() > 1)
        *(--str.end()) = ']';
    else
        str.append(1, ']');*/

    str += "{" + buf + "}";
	getchar();
	return 0;
}

