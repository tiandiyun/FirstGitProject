// TestThread.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <ctime>
#include "TestLock.h"

void init_number_generator()
{
	static bool done = false;
	if (!done)
	{
		done = true;
		std::srand(static_cast<unsigned int>(std::time(0)));
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
    // TestConditionVarible();

    // TestUniqLock();

    TestConditionUniqLock();

    system("pause");
	return 0;
}

