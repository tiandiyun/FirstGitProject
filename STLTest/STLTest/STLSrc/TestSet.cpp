#include "stdafx.h"
#include "TestSet.h"
#include <iostream>
#include <set>
#include <unordered_set>
#include <list>
#include <deque>
#include "../AutoPtrInherit.h"

void TestUnorderedSet()
{
    std::unordered_set<int> iSet;
    iSet.emplace(5);
    iSet.emplace(3);
    iSet.emplace(2);
    iSet.emplace(4);
    iSet.emplace(1);
    for (int i : iSet)
    {
        std::cout << i << std::endl;
    }

    std::unordered_set<int> tmpSet;
    tmpSet.swap(iSet);
}

void EmplaceToSet()
{
    std::list<Base> bSet;
    Base b;
    bSet.emplace_back(std::move(b));
}

void TraversalEraseSet()
{
    std::set<int> iSet;
    iSet.emplace(5);
    iSet.emplace(3);
    iSet.emplace(2);
    iSet.emplace(4);
    iSet.emplace(1);
    
    auto it = iSet.begin();
    while (it != iSet.end())
    {
        it = iSet.erase(it);
    }
}

