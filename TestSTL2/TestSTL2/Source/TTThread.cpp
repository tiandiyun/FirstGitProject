#include "TTThread.h"
#include <thread>
#include "..//Util/DataStruct.h"


void CreateStaticVar(int i)
{
	static Base b(i);
	printf("CreateStaticVar Over : %d\n", i);
}

void TestMultiThreadStatic()
{
	std::thread t1(CreateStaticVar, 1);
	std::thread t2(CreateStaticVar, 2);
	t1.join();
	t2.join();
}