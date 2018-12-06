#include "test_thread.h"

#include <boost/thread.hpp> 
#include <iostream> 
#include <cstdlib> 
#include <ctime> 
#include <time.h>

boost::mutex mt;

/*
void init_number_generator()
{
	static bool done = false;

	boost::lock_guard<boost::mutex> lock(mt);
	if (!done)
	{
		std::cout << "init srand generator by thread: " << boost::this_thread::get_id() << std::endl;
		done = true;
		std::srand(static_cast<unsigned int>(std::time(0)));
	}
}*/

/*
void init_number_generator()
{
	static boost::thread_specific_ptr<bool> tls;
	boost::lock_guard<boost::mutex> lock(mt);
	if (!tls.get())
		tls.reset(new bool(false));
	if (!*tls)
	{
		std::cout << "init srand generator by thread: " << boost::this_thread::get_id() << std::endl;
		*tls = true;
		std::srand(static_cast<unsigned int>(std::time(0)));
	}
}*/


boost::mutex io_mutex;
boost::thread_specific_ptr<int> ptr;
struct count
{
	count(int id) : id(id) { }

	void operator()()
	{
		boost::lock_guard<boost::mutex> lock(mt);
		if (ptr.get() == 0)
		{
			std::cout << "init count reset by : " << id << std::endl;
			ptr.reset(new int(0));
		}

		for (int i = 0; i < 10; ++i)
		{
			(*ptr)++;
			boost::mutex::scoped_lock lock(io_mutex);
			std::cout << id << ": " << *ptr << std::endl;
		}
	}

	int id;
};

struct parmData
{
	parmData()
	{
		std::cout << "parmData()" << std::endl;
	}
	parmData(const parmData& oth)
	{
		a = oth.a;
		b = oth.b;
		std::cout << "parmData(const parmData& oth)" << std::endl;
	}
	~parmData()
	{
		std::cout << "~parmData()" << std::endl;
		a = 10;
		b = 11;
	}
	parmData& operator=(const parmData& oth)
	{
		a = oth.a;
		b = oth.b;
		std::cout << "operator=" << std::endl;
	}

	int a{ 1 };
	int b{ 2 };
};

using AsyncFunc = std::function<void()>;
void GetAsyncParamsByVal(int v)
{
	std::cout << "GetAsyncParamsByVal: " << v << std::endl;
}

void GetAsyncParamsByRef(int& v)
{
	std::cout << "GetAsyncParamsByRef: " << v << std::endl;
}

void TestAsyncParamsByRef(const parmData& data)
{
	std::cout << data.a << ":" << data.b << std::endl;
}

void AsyncCallFunc(std::list<AsyncFunc>& funcs)
{
	Sleep(2);
	for (auto f: funcs)
	{
		f();
	}
}


void emitThread()
{
	/*boost::thread t[2];
	int size = sizeof(t) / sizeof(t[0]);

	for (int i = 0; i < size; ++i)
		//t[i] = boost::thread(init_number_generator);
		t[i] = boost::thread(count(i));

	for (int i = 0; i < size; ++i)
		t[i].join();*/

	/*boost::thread glbTh;

	{
		std::list<AsyncFunc> funcArray;

		parmData pd;
		pd.a = 3;
		pd.b = 4;

		parmData temp = pd;
		funcArray.push_back([&temp](){
			TestAsyncParamsByRef(temp);
		});

		glbTh = boost::thread(AsyncCallFunc, funcArray);

		pd.a = 5;
		pd.b = 6;
	}

	glbTh.join();

	Sleep(10);*/

	std::function<void()> func;
	{
		parmData pd;
		parmData* p = &pd;
		pd.a = 3;
		pd.b = 4;
		func = [=]() {
			TestAsyncParamsByRef(pd);
		};

		pd.a = 5;
		pd.b = 6;
	}

	getchar();

	func();
}