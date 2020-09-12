
#pragma once

#include <algorithm>
#include <iostream>
#include <memory>
#include <list>

static int ExtVal2 = 10;

class Base
{
public:
    Base()
    {
        std::cout << "Base() Addr: 0x" << std::hex << (int)this << std::endl;
    }

    Base(int param1) : mParam1(param1)
    {
        std::cout << "Base(int) Addr: 0x" << std::hex << (int)this << std::endl;
    }

    Base(int param1, int param2) : mParam1(param1), mParem2(param2)
    {
        std::cout << "Base(int, int) Addr: 0x" << std::hex << (int)this << std::endl;
    }

    Base(const Base& b) : mParam1(b.mParam1), mParem2(b.mParem2)
    {
        std::cout << "Base(const Base&) Addr: 0x" << std::hex << (int)this << std::endl;
    }

    Base(const Base&& b) noexcept : mParam1(b.mParam1), mParem2(b.mParem2)
    {
        std::cout << "Base(const Base&&) Addr: 0x" << std::hex << (int)this << std::endl;
    }

    ~Base()
    {
        std::cout << "~Base() Addr: 0x" << std::hex << (int)this << std::endl;
    }

    Base& operator=(const Base& b)
    {
        std::cout << "operator=(const Base&)" << std::endl;
        return *this;
    }

    Base& operator=(const Base&& b) noexcept
    {
        std::cout << "Base& operator=(const Base&&)" << std::endl;
        return *this;
    }

    int operator-(const Base& b)
    {
        std::cout << "operator-(const Base&)" << std::endl;
        return this->mParam1 - b.mParam1;
    }

    int operator-(const Base&& b)
    {
        std::cout << "operator-(const Base&&)" << std::endl;
        return this->mParam1 - b.mParam1;
    }

    int operator+(const Base& b)
    {
        std::cout << "operator+(const Base&)" << std::endl;
        return this->mParam1 + b.mParam1;
    }

    int operator+(const Base&& b)
    {
        std::cout << "operator+(const Base&&)" << std::endl;
        return this->mParam1 + b.mParam1;
    }

    void CallRValueFunc(const Base&& b)
    {
        std::cout << "CallRValueFunc(const Base&& b)" << std::endl;
    }

    void SetParam1(int param) 
    { 
        mParam1 = param; 
    }

    int GetParam1()
    {
        return mParam1;
    }

    void SetParam2(int param)
    {
        mParem2 = param;
    }

    int GetParam2()
    {
        return mParem2;
    }

public:
    virtual Base* Show()
    {
        std::cout << "Base::Show" << std::endl;
        return this;
    }

private:
    int mParam1{ 100 };
    int mParem2{ 200 };
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


struct Fish
{
    Fish()
    {
        std::cout << "Fish()" << std::endl;
    }

    Fish(const Fish& fish)
    {
        id = fish.id;
        type = fish.type;
        kind = fish.kind;
        worth = fish.worth;
        std::cout << "Fish(const Fish& fish)" << std::endl;
    }

    Fish(int i, int t, int k, int w, float s)
        : id(i), type(t), kind(k), worth(w), leftSeconds(s)
    {
        std::cout << "Fish(int i, int t, int k, int w, float s)" << std::endl;
    }

    Fish& operator=(const Fish& fish)
    {
        id = fish.id;
        type = fish.type;
        kind = fish.kind;
        worth = fish.worth;
        std::cout << "operator=" << std::endl;
        return *this;
    };

    Fish& operator +=(const Fish& other)
    {
        worth += other.worth;
        return *this;
    }

    Fish operator +(const Fish& other)
    {
        Fish tempFish = *this;
        tempFish.worth += other.worth;
        return tempFish;
    }

    ~Fish()
    {
        std::cout << "~Fish()" << std::endl;
    }

    Fish& operator()()
    {
        return *this;
    }

    int id{ 1 };
    int type{ 2 }; // 类型
    int kind{ 3 }; // 种类
    int worth{ 4 }; // 倍数
    float leftSeconds{ 5.f }; // 剩余存活时间
};

typedef std::shared_ptr<Fish> FishPtr;
typedef std::list<FishPtr> FishList;


struct DataTestAlign
{
    char    a;
    int     b;
};

struct Data
{
    Data() : Data(0) {}
    Data(int v) : v(v){}
    int v;
};



// TODO:  在此处引用程序需要的其他头文件
