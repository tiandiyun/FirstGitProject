// TestSingleton.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include "SingletonLazy.h"
#include "Singleton.h"

class sigA : public SingletonLazy<sigA>
{
public:
    sigA()
    {
        std::cout << "sigA()" << std::endl;
    }

    int GetA() { return a; }

private:
    int a = 1;
};

class sigB : public Singleton<sigB>
{
public:
    sigB()
    {
        std::cout << "sigB()" << std::endl;
    }

    int GetB() { return b; }

private:
    int b = 2;
};

class sigC : public sigA
{
public:
    sigC()
    {
        std::cout << "sigC()" << std::endl;
    }

    int GetC() 
    { 
        return c; 
    }

private:
    int c = 3;
};

class sigD : public sigB
{
public:
    sigD()
    {
        std::cout << "sigD()" << std::endl;
    }

    int GetD()
    {
        return d;
    }

private:
    int d = 4;
};

void func()
{
    sigD d;
}

int _tmain(int argc, _TCHAR* argv[])
{
//     std::cout << std::ios::hex << &(sigA::Instance()) << ": " << sigA::Instance().GetA() << std::endl;
//     std::cout << std::ios::hex << &(sigB::Instance()) << ": " << sigB::Instance().GetB() << std::endl;

    //sigC::Instance();

   /* sigA<sigA> sa;*/


    sigD d;
    sigD::getSingleton();
    sigB::getSingleton();
    func();


    /*sigC::Instance();
    sigA::Instance();*/

    system("pause");
	return 0;
}

