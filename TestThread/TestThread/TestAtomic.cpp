#include "stdafx.h"
#include "TestAtomic.h"
#include <atomic>

void TestAtomicExchange()
{
	/*int expected = 1;
	std::atomic<int> a = 1;
	bool r = a.compare_exchange_weak(expected, 3);*/

	//因为compare_exchange_weak()可以“伪失败”，所以这里通常使用一个循环：

	bool expected = false;
	std::atomic<bool> b = true; // 设置些什么
	while (!b.compare_exchange_weak(expected, true) && !expected);


	//在这个例子中，循环中expected的值始终是false，表示compare_exchange_weak()会莫名的失败。
}