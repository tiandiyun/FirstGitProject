#include "stdafx.h"
#include "TestVector.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include "../DataStruct.h"

void TestVectorEmplace()
{
    std::vector<Fish> fishVec;
    fishVec.emplace_back(Fish());
    fishVec.emplace_back(Fish());
    for (auto fishData : fishVec)
    {
        int i = 0;
    }

    fishVec.clear();
    for (int i = 0; i < 3; ++i)
    {
        fishVec.emplace(fishVec.begin(), Fish());
        std::cout << "-------------" << std::endl;
    }
}

void TestFindIfInVector()
{
    int l = 3, u = 7;
    std::vector<int> vec;
    for (int i = 0; i < 10; ++i)
    {
        vec.emplace_back(i * 2);
    }

    auto begIt = std::find_if(vec.begin(), vec.end(), [&l](int& d) { return d >= l; });
    auto endIt = std::find_if(vec.begin(), vec.end(), [&u](int& d) { return d >= u; });

    std::cout << *begIt << ", " << *endIt << std::endl;
}

void TestEmplaceVector()
{
    std::vector<Base> baseVec;

    /*{
        Base b1(1, 1);
        baseVec.emplace_back(b1);
    }
    std::cout << "-----------------------------" << std::endl;*/

    {
        Base b2(2, 2);
        baseVec.emplace_back(std::move(b2));
    }
    std::cout << "-----------------------------" << std::endl;

    /*{
        baseVec.emplace_back(Base());
    }
    std::cout << "-----------------------------" << std::endl;*/
}