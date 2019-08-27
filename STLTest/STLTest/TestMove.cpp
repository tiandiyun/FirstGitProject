#include "stdafx.h"
#include "TestMove.h"
#include <xutility>
#include <iostream>
#include <vector>
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
