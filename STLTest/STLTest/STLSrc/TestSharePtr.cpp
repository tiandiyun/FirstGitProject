#include "stdafx.h"
#include "TestSharePtr.h"
#include "../DataStruct.h"
#include <map>

void TestSharePtrInSTL()
{
    FishList fishes;
    for (int i = 0; i < 5; ++i)
    {
        fishes.push_back(FishPtr(new Fish()));
    }

    for (FishPtr& fish : fishes)
    {
        Fish& fs = *fish;
        int id = fish->id;
        printf("%d", id);
    }

    std::map<int, Fish> fishMap;
    Fish f;
    fishMap[0] = f;
}

void TestAutoDestroy()
{
    FishList fishes;
    fishes.push_back(std::make_shared<Fish>());
}
