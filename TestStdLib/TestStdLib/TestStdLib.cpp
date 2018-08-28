// TestStdLib.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

using namespace std;

void TestDiv()
{
    div_t dv = div(5, 3);
    cout << "div(5, 3) -- quot: " << dv.quot << ", rem: " << dv.rem << endl;

    dv = div(4, 2);
    cout << "div(4, 2) -- quot: " << dv.quot << ", rem: " << dv.rem << endl;
}


int _tmain(int argc, _TCHAR* argv[])
{
    TestDiv();

    system("pause");
	return 0;
}

