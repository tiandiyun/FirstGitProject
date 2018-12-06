// TestOperator.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

class O{};

class A
{
public:
    O operator << (O& o)
    {
        std::cout << "O A::operator << (O& o)" << std::endl;
        return o;
    }
};

class B
{
public:
    A operator << (A& a)
    {
        std::cout << "A B::operator << (A& a)" << std::endl;
        return a;
    }
};

class C
{
public:
    B operator << (B& b)
    {
        std::cout << "B C::operator << (B& b)" << std::endl;
        return b;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    O o;
    A a;
    B b;
    C c;

    c << b << a << o;

    system("pause");
    return 0;
}

