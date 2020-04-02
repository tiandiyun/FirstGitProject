#include "stdafx.h"
#include <vector>
#include <iostream>


void TestReverseIterator()
{
    std::vector<int> intVec;
    for (int i = 0; i < 5; ++i)
    {
        intVec.emplace_back(i);
    }

    std::vector<int>::iterator sIt = intVec.begin() + 3;
    std::vector<int>::reverse_iterator rIt(sIt + 1);
    std::vector<int>::iterator pIt = (rIt + 1).base();
    std::vector<int>::iterator pIt2 = rIt.base() - 1;

    std::cout << "sIt: " << *sIt << std::endl;
    std::cout << "rIt: " << *rIt << std::endl;
    std::cout << "pIt: " << *pIt << std::endl;
    std::cout << "pIt2: " << *pIt2 << std::endl;
}