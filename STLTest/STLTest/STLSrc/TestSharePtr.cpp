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

void TestWeakPtr()
{
    std::weak_ptr<int> refPtr;
    {
        std::shared_ptr<int> sharePtr = nullptr/*std::make_shared<int>(5)*/;
        refPtr = sharePtr;
        std::cout << refPtr.expired() << ", " << refPtr.use_count() << std::endl;
        auto tmpPtr = refPtr.lock();
        std::cout << refPtr.expired() << ", " << refPtr.use_count() << std::endl;
    }

    std::cout << refPtr.expired() << ", " << refPtr.use_count() << std::endl;
    if (refPtr.lock() == nullptr)
    {
        std::cout << "weak_ptr is null" << std::endl;
    }
    auto tmpPtr = refPtr.lock();
}