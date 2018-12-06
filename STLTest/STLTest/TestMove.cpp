#include "TestMove.h"
#include "stdafx.h"
#include <xutility>
#include <iostream>

void TestMoveString()
{
    std::string srcStr = "temp";
    std::string dstStr = std::move(srcStr);
}
