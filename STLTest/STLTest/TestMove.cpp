#include "stdafx.h"
#include "TestMove.h"
#include <xutility>
#include <iostream>
#include <vector>
#include <sstream>
#include "DataStruct.h"

void TestMoveString()
{
    std::string srcStr = "temp";
    std::string dstStr = std::move(srcStr);
}

void TestMoveData()
{
    Base data1;
    Base data2;

    std::cout << "The case of direct assignment:    ";
    data1 = data2;

    std::cout << "The case of rvalue assignment:    ";
    data1 = std::move(data2);

    std::cout << "Construction by direct assignment:    ";
    Base data3 = data2;

    std::cout << "Construction by rvalue assignment:    ";
    Base data4 = std::move(data2);

    std::cout << "-----------" << std::endl;
    std::vector<Base> dataVec;
    dataVec.emplace_back(data1);
    dataVec.emplace_back(std::move(data2));
}

void TestEmplace()
{
    std::vector<Base> dataVec;

    {
        dataVec.emplace_back(Base());
    }

    std::cout << "----------------------" << std::endl;

    {
        Base b;
        dataVec.emplace_back(b);
        std::cout << "0x" << std::hex << (int)&(dataVec.back()) << std::endl;
    }
}


static std::string ThroughBlocks2String(std::vector<int>& throughBlocksCount)
{
    const char* blockNames[] = { "Gap", "Comm", "Red", "Move", "Ice", "Meteor", "Board" };
    size_t size = (std::min)(sizeof(blockNames), throughBlocksCount.size());

    std::stringstream ss;
    size_t i = 0;
    for (; i < size; ++i)
    {
        ss << ", " << blockNames[i] << " : " << throughBlocksCount[i];
    }

    for (; i < throughBlocksCount.size(); ++i)
    {
        ss << ", " << "none-name " << i << " : " << throughBlocksCount[i];
    }

    return ss.str();
}

void TestMoveTemporaryString()
{
    std::vector<int> throughBlocksCount;
    for (int i = 0; i < 7; ++i)
    {
        throughBlocksCount.push_back(i);
    }

    std::string&& buffer = ThroughBlocks2String(throughBlocksCount);
    std::cout << buffer << std::endl;
}