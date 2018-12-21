#include "stdafx.h"
#include "TestMove.h"
#include <xutility>
#include <iostream>

void TestMoveString()
{
    std::string srcStr = "temp";
    std::string dstStr = std::move(srcStr);
}
