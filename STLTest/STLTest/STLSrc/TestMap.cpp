#include "stdafx.h"
#include "TestMap.h"
#include <map>
#include <time.h>
#include <unordered_map>
#include "../DataStruct.h"


void TestMapAccess()
{
	std::map<int, int> data;
	data[0] = 0;
	data[1] = 1;
	data[2] = 2;

	auto it = data.find(0);
	if (it != data.end())
	{
		it->second += 3;
	}

	for (auto& d : data)
	{
		d.second += 2;
	}

	for_each(data.begin(), data.end(), [](std::pair<int, int> dataPair) { std::cout << dataPair.first << ", " << dataPair.second << std::endl; });

	/*auto it = data.begin();
	while (it != data.end())
	{
	it = data.erase(it);
	}*/
}

void TestMapCopy()
{
	std::map<int, int> srcMap;
	srcMap[0] = 0;
	srcMap[1] = 1;
	srcMap[2] = 2;

	std::map<int, int> dstMap = srcMap;
	dstMap[0] = 5;
	dstMap[2] = 7;
}

void TestMapEmplace()
{
	std::map<int, std::map<int, Fish>> playerFishMap;
	std::map<int, Fish> fishMap;
	/*fishMap[0];
	fishMap[1] = Fish();*/
	fishMap.insert(std::make_pair(1, Fish()));
	std::cout << "-----------------------" << std::endl;
	fishMap.emplace(2, Fish());
	//playerFishMap[0] = fishMap;

	//std::map<int, std::string> m{ { 0, "t" } };
}

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
    srand(static_cast<uint32_t>(time(nullptr)));

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


void TestMultiMap()
{
	std::multimap<char, int> mymm;

	mymm.insert(std::make_pair('x', 10));
	mymm.insert(std::make_pair('y', 20));
	mymm.insert(std::make_pair('z', 30));
	mymm.insert(std::make_pair('z', 40));
	mymm.insert(std::make_pair('a', 60));

	std::multimap<char, int>::iterator it = mymm.find('x');
	auto v = *it;

	std::multimap<char, int>::iterator itz = mymm.find('z');
	auto vz = *itz;

	std::multimap<char, int>::size_type size = mymm.count('z');

	for (std::multimap<char, int>::iterator ittemp = itz; ittemp != mymm.end(); ++ittemp)
	{
		std::cout << (*ittemp).second << std::endl;
	}
}

void TestMapFind()
{
    std::map<int, Fish> fishMap;
    fishMap.emplace(std::make_pair(1, Fish()));
    fishMap.emplace(2, Fish());
    auto it = std::find_if(fishMap.begin(), fishMap.end(), [](const std::pair<int, Fish>& fishPari){
        /*std::cout << fishPari.first << std::endl;*/
        return true;
    });
}

void MapInsertByOrder()
{
    std::map<int, int> orderedMap;
    orderedMap[3] = 0;
    orderedMap[0] = 3;
    orderedMap[2] = 1;
    orderedMap[1] = 2;

    std::unordered_map<int, int> unorderedMap;
    unorderedMap[3] = 0;
    unorderedMap[0] = 3;
    unorderedMap[2] = 1;
    unorderedMap[1] = 2;
    
    for (auto& mp : orderedMap)
    {
        std::cout << mp.first << ",";
    }
    std::cout << std::endl;

    for (auto& mp : unorderedMap)
    {
        std::cout << mp.first << ",";
    }
    std::cout << std::endl;
}