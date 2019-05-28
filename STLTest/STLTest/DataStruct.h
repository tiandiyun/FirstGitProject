
#pragma once

#include <algorithm>
#include <iostream>
#include <memory>
#include <list>

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
