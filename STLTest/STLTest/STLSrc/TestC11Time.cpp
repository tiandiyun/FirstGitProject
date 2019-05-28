#include "stdafx.h"
#include "TestC11Time.h"
#include <iostream>
#include <thread>

void TestRep()
{
    /*std::chrono::duration<int> two(2);
    std::chrono::duration<double, std::ratio<60>> thirty(0.5);

    std::cout << "sizeof(duration<int>) is : " << sizeof(decltype(two)::rep) << std::endl;
    std::cout << "duration<double, std::ratio<60>> is : " << sizeof(decltype(thirty)::rep) << std::endl;

    std::cout << "two(2) is : " << two.count() << std::endl;
    std::cout << "thirty(0.5) is : " << thirty.count() << std::endl;

    auto ad = two + thirty;
    std::cout << "type name of (two + thirty) is " << typeid(ad).name() << std::endl;
    std::cout << "sizeof(two + thirty) is " <<sizeof(decltype(ad)::rep) << std::endl;//8
    std::cout << ad.count() << "\t" << decltype(ad)::period::num << "/" << decltype(ad)::period::den << std::endl;//32  1/1

    return;*/

    /*std::chrono::minutes a(30);
    std::chrono::seconds b = a;             //OK
    //std::chrono::minutes c = b;             //compile error

    std::chrono::duration<double, std::ratio<60>> d(3);
    //std::chrono::seconds e = d;             //compile error
    std::chrono::duration<double> f = d;    //OK*/

    using shakes = std::chrono::duration<int, std::ratio<1, 100000000>>;
    using jiffies = std::chrono::duration<int, std::centi>;
    using microfortnights = std::chrono::duration<float, std::ratio<12096, 10000>>;
    using nanocenturies = std::chrono::duration<float, std::ratio<3155, 1000>>;

    std::chrono::seconds sec(1);

    std::cout << "1 second is:\n";

    // 无精度损失的整数尺度转换：无转型
    std::cout << std::chrono::microseconds(sec).count() << " microseconds\n"
        << shakes(sec).count() << " shakes\n"
        << jiffies(sec).count() << " jiffies\n";

    // 有精度损失的整数尺度转换：需要转型
    std::cout << std::chrono::duration_cast<std::chrono::minutes>(sec).count()
        << " minutes\n";

    // 浮点尺度转换：无转型
    std::cout << microfortnights(sec).count() << " microfortnights\n"
        << nanocenturies(sec).count() << " nanocenturies\n";
}

void TestCustomDuration()
{
    using half_second = std::chrono::duration<float, std::ratio<1, 2> >;

    std::chrono::seconds s{ 1 };
    std::cout << "use second : " << s.count() << std::endl;

    half_second ss{ 1 };
    std::cout << "use half_second : " << ss.count() << std::endl;
    std::cout << "use half_second : " << half_second(4).count() << std::endl;
    std::cout << "use half_second : " << half_second(s).count() << std::endl;

    std::chrono::minutes m{ 1 };
    std::cout << "use half_second : " << half_second(m).count() << std::endl;

    std::chrono::system_clock::time_point tt1 = std::chrono::system_clock::now();
    //std::this_thread::sleep_for(std::chrono::seconds(1));
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::chrono::system_clock::time_point tt2 = std::chrono::system_clock::now();
    std::cout << (tt2 - tt1).count() << " tick count" << "\t" << std::chrono::duration_cast<std::chrono::milliseconds>(tt2 - tt1).count() << std::endl;

    std::chrono::system_clock::time_point tt3 = std::chrono::system_clock::now();
    //std::this_thread::sleep_for(half_second(1));
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::chrono::system_clock::time_point tt4 = std::chrono::system_clock::now();
    std::cout << (tt4 - tt3).count() << " tick count" << "\t" << std::chrono::duration_cast<std::chrono::milliseconds>(tt4 - tt3).count() << std::endl;

    std::chrono::minutes t1(10);
    std::chrono::seconds t2(60);
    std::chrono::seconds t3 = t1 - t2;
    std::cout << t3.count() << " second" << std::endl;

    std::cout << std::chrono::duration_cast<std::chrono::minutes>(t3).count() << " minutes" << std::endl;
}
