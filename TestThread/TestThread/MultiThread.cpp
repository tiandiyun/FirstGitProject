#include "stdafx.h"
#include "MultiThread.h"
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include "CustomThread.h"

using namespace std;

class MyClass
{
public:
	MyClass()
	{
		cout << "MyClass" << endl;
	}

	static MyClass& Instance()
	{
		//this_thread::sleep_for(std::chrono::seconds(1));
		static MyClass cls;
		return cls;
	}

	~MyClass()
	{

	}
};

static void GetClass()
{
	MyClass::Instance();
}

void TestMultiThreadStatic()
{
	std::thread t1(GetClass);
	std::thread t2(GetClass);
	std::thread t3(GetClass);
	std::thread t4(GetClass);
	std::thread t5(GetClass);

	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
}

static void* ThreadCustomCallFunc(void*)
{
    std::cout << "thread: " << CustomThread::CovertThrdT(CustomThread::CurrentThreadID()) << std::endl;
    return nullptr;
}

void TestCustomThread()
{
    CustomThread t1(ThreadCustomCallFunc, NULL);
//     CustomThread t2(ThreadCustomCallFunc, NULL);
//     CustomThread t3(ThreadCustomCallFunc, NULL);

    /*if (t1.Joinable())
    {
        cout << "t1 is joinable" << endl;
    }
    else
    {
        cout << "t1 is not joinable" << endl;
    }*/

    t1.Join();
//     t2.Join();
//     t3.Join();

    if (t1.Joinable())
    {
        cout << "t1 is joinable" << endl;
    }
    else
    {
        cout << "t1 is not joinable" << endl;
    }

    CustomThread::SleepForSecs(3);
}