#include "TTStlContainer.h"
#include <iostream>
#include <map>

void TestMapOverFlow()
{
	std::map<unsigned char, int> srcMap;
	srcMap[1] = 10;

	int key = 0x101;

	auto it = srcMap.find(key);
	if (it != srcMap.end())
	{
		std::cout << it->second << std::endl;
	}
}

void TestContainerAddSelf()
{
	std::map<int, int> digitMap;
	digitMap[0] = 0;
	std::cout << "before self add, digitMap[0]= " << digitMap[0] << std::endl;

	digitMap[0]++;
	std::cout << "after self add, digitMap[0]= " << digitMap[0] << std::endl;
}