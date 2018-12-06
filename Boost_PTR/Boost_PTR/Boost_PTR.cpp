// Boost_PTR.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <boost/function.hpp> 
#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include "test_boost_signal.h"
#include "test_thread.h"
#include "plugin_dump.h"
#include "jsonParser.h"
#include "testDataTime.h"
#include "AutoPtrInherit.h"

class A
{
public:
	A() : v(NULL) { std::cout << "A()" << std::endl; }
	A(const A& a) : v(NULL) { std::cout << "A(const A& a)" << std::endl; }
	~A(){ std::cout << "~A()" << std::endl; }
	A& operator=(const A& a) { std::cout << "A& operator=" << std::endl;  return *this; }
protected:
private:
	int* v;
};

A getA()
{
	A a;
	return a;
}

struct world
{
	void hello(std::ostream &os)
	{
		os << "Hello, world!" << std::endl;
	}
};

void TestBindFunc()
{
    boost::function<void(world*, std::ostream&)> f = &world::hello;
    world w;
    f(&w, boost::ref(std::cout));

    auto stdLambFunc = [](int& num)->void{
        std::cout << num << std::endl;
    };

    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    std::for_each(vec.begin(), vec.end(), std::bind(stdLambFunc, std::placeholders::_1));
}

void TestSharePtr()
{
    std::shared_ptr<int> p1(new int());
    std::cout << "used count of p1: " << p1.use_count() << std::endl;
    {
        /*
        std::shared_ptr<int> p2(p1);
        std::cout << "used count of p1: " << p1.use_count() << std::endl;
        std::cout << "used count of p2: " << p2.use_count() << std::endl;*/

        int* pInt = p1.get();
        std::cout << "used count of p1: " << p1.use_count() << std::endl;

        /*std::weak_ptr<int> p3(p1);
        std::cout << "used count of p1: " << p1.use_count() << std::endl;
        std::cout << "used count of p3: " << p3.use_count() << std::endl;

        p1.reset();
        std::cout << "used count of p1: " << p1.use_count() << std::endl;
        //std::cout << "used count of p2: " << p2.use_count() << std::endl;
        std::cout << "used count of p3: " << p3.use_count() << std::endl;*/

        /*
        p2 = p1;
        //p2.swap(p1);
        std::cout << "used count of p1: " << p1.use_count() << std::endl;
        std::cout << "used count of p2: " << p2.use_count() << std::endl;*/
    }
    //	std::cout << "used count of p1: " << p1.use_count() << std::endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
    /*TestBindFunc();*/

	/*signalFunc();*/

	/*emitThread();*/

    /*TestTraceStack();*/

    /*generate_user();
    read_user();*/
    //read_json_data_from_string();

    /*CompareDate();*/

    TestAutoPtrInherit();

	getchar();
	return 0;
}

