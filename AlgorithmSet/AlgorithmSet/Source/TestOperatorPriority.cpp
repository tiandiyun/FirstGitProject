#include "TestOperatorPriority.h"
#include <iostream>

class A
{
};

A& operator || (A& a1, A& a2)
{
	std::cout << " || " << std::endl;
	return a1;
}

A& operator&&(A& a1, A& a2)
{
	std::cout << " && " << std::endl;
	return a1;
}

void TestCompareOperator()
{
	//auto a = true && false || false;
	A a1, a2, a3;
	//auto a = a1 || a2 && a3;
	auto a = a1 && a2 || a3;
}
