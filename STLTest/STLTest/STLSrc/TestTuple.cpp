#include "stdafx.h"
#include "TestTuple.h"
#include <tuple>
#include <iostream>

void TestTupleInitial()
{
    std::tuple<int, int, int> intTuple[] =
    {
        std::tuple<int, int, int>{ 9, 8, 7 },
        std::tuple<int, int, int>{ 1, 2, 3 },
        std::tuple<int, int, int>{ 4, 5, 6 }
    };

    for (std::tuple<int, int, int> &tup : intTuple)
    {
        std::cout << std::get<0>(tup) << ", " << std::get<1>(tup) << ", " << std::get<2>(tup) << std::endl;
    }


#define CreateCombNameTuple(combType) std::tuple<int, const char*>{ DdzRbt_SINGLE, #combType}

#define GetName(combType) #combType

    enum
    {
        DdzRbt_SINGLE
    };

    auto tp = CreateCombNameTuple(DdzRbt_SINGLE);

    const char * combNameInfo[] =
    {
        GetName(DdzRbt_SINGLE),         //¥ÌŒÛ¿‡–Õ

    };
    //auto tp = std::tuple<int, const char*>{ DdzRbt_SINGLE, "haha"};
}