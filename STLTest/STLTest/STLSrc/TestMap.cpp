#include "stdafx.h"
#include "TestMap.h"
#include <map>
#include <time.h>
#include "../DataStruct.h"


void TraversalSetMap()
{
    std::map<int, Base> baseMap;
    baseMap.emplace(0, Base());

    for (auto pair : baseMap)
    {
        pair.second.SetParam1(33);
    }

    for (auto &pair : baseMap)
    {
        pair.second.SetParam1(33);
    }
}

void TraversalDeleteMap()
{
    srand(time(nullptr));

    std::map<int, int> intMap;
    for (int i = 0; i < 10; ++i)
    {
        int key = rand() % 10000;
        int value = rand() % 10000;
        intMap[key] = value;
    }

    auto begIt = intMap.begin();

    for (auto &pair : intMap)
    {
        std::cout << pair.second << std::endl;
    }

    for (auto it = intMap.begin(); it != intMap.end();)
    {
        intMap.erase(it++);
    }
}

using DdzRbtHandCards = std::map<uint8_t, uint8_t>;

DdzRbtHandCards & operator-=(DdzRbtHandCards &srcHands, const DdzRbtHandCards &othHands)
{
    for (auto it2 = othHands.begin(); it2 != othHands.end(); ++it2)
    {
        auto it1 = srcHands.find(it2->first);
        it1->second -= it2->second;
        if (it1->second == 0)
        {
            srcHands.erase(it1);
        }
    }

    return srcHands;
}

void TestHandCardsOP()
{
    DdzRbtHandCards srcHands;
    srcHands[0] = 0;
    srcHands[1] = 1;
    srcHands[2] = 2;
    srcHands[5] = 6;
    srcHands[7] = 8;

    DdzRbtHandCards othHands;
    othHands[5] = 5;
    othHands[7] = 7;

    srcHands -= othHands;

    int a = 0;
    std::cout << (a += 1) << std::endl;
}