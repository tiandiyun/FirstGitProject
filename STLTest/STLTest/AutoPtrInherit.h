#ifndef _TEST_AUTO_PTR_INHERIT_H_
#define _TEST_AUTO_PTR_INHERIT_H_

#include <iostream>

extern int ExtVal[];

static int ExtVal2 = 10;

class Base
{
public:
    Base() : param(100)
    {
        std::cout << "Base()" << std::endl;
    }

    Base(int data) : param(data)
    {
        std::cout << "Base(int)" << std::endl;
    }

    Base(const Base& b) : param(b.param)
    {
        std::cout << "Base(const Base&)" << std::endl;
    }

    Base(const Base&& b)
    {
        std::cout << "Base(const Base&&)" << std::endl;
    }

    ~Base()
    {
        std::cout << "~Base()" << std::endl;
    }

    Base& operator=(const Base& b)
    {
        std::cout << "operator=(const Base&)" << std::endl;
        return *this;
    }

    Base& operator=(const Base&& b)
    {
        std::cout << "Base& operator=(const Base&&)" << std::endl;
        return *this;
    }

    int operator-(const Base& b)
    {
        std::cout << "operator-(const Base&)" << std::endl;
        return this->param - b.param;
    }

    int operator-(const Base&& b)
    {
        std::cout << "operator-(const Base&&)" << std::endl;
        return this->param - b.param;
    }

public:
    virtual Base* Show()
    {
        std::cout << "Base::Show" << std::endl;
        return this;
    }

private:
    int param;
};

class Derive : public Base
{
public:
    Base* Show() override
    {
        std::cout << "Derive::Show" << std::endl;
        return this;
    }

    int dp = 0;
};

void TestVecEmplace();

void TestListEmplace();

void BasePtrToDerive();

#endif