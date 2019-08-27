#include "stdafx.h"
#include "AutoPtrInherit.h"
#include <typeinfo>
#include <vector>
#include <list>
#include "DataStruct.h"


int ExtVal[10] = { 1, 2, 3, 4, 0 };


void TestVecEmplace()
{
    std::vector<Base> baseList;
    baseList.emplace_back(1);
    baseList.emplace_back(2);
    baseList.emplace_back(3);
    baseList.emplace_back(4);

    std::cout << "=============== SPLITE LINE ===================" << std::endl;

    /*std::vector<Base> tmpList;
    std::cout << "tmpList capacity: " << tmpList.capacity() << std::endl;

    for (const Base& b : baseList)
    {
        tmpList.emplace_back(b);
        std::cout << "------------------" << std::endl;
    }

    std::cout << "=============== SPLITE LINE ===================" << std::endl;

    baseList.clear();*/


    /*std::vector<Base> tmpList;
    tmpList.swap(baseList);*/

    std::vector<Base> tmpList;
    tmpList.assign(baseList.begin(), baseList.end());

    std::cout << "=============== SPLITE LINE ===================" << std::endl;
}

void TestListEmplace()
{
    std::list<Base> baseList;
    baseList.emplace_back(1);
    baseList.emplace_back(2);
    baseList.emplace_back(3);
    baseList.emplace_back(4);

    std::cout << "=============== SPLITE LINE ===================" << std::endl;

    std::list<Base> tmpList;
    for (const Base& b : baseList)
    {
        tmpList.emplace_back(b);
        std::cout << "------------------" << std::endl;
    }

    std::cout << "=============== SPLITE LINE ===================" << std::endl;

    baseList.clear();

    /*std::vector<Base> tmpList;
    tmpList.swap(baseList);*/

    std::cout << "=============== SPLITE LINE ===================" << std::endl;
}

void BasePtrToDerive()
{
    Base* bp = new Derive();
    
    Base& br = *bp;
    br.Show();
}
