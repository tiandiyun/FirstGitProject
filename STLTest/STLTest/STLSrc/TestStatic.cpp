#include "stdafx.h"
#include <iostream>
#include "TestStatic.h"

void PrintStaticLocalVariable()
{
	static int a = 1;
	std::cout << "&a : " << std::ios::hex << &a << ", a = " << std::ios::dec << a << std::endl;
	a++;
}

void TestStaticLocalVariable()
{
	PrintStaticLocalVariable();
	PrintStaticLocalVariable();
}