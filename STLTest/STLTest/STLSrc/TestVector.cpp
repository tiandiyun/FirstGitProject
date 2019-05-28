#include "stdafx.h"
#include "TestVector.h"
#include <algorithm>
#include <iostream>

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
