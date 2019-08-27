#include "stdafx.h"
#include "FunctionParams.h"
#include <iostream>

void ParamsInStatck(int a, int b, int c)
{
    std::cout << "&a: " << std::ios::hex << &a << std::endl;
    std::cout << "&b: " << std::ios::hex << &b << std::endl;
    std::cout << "&c: " << std::ios::hex << &c << std::endl;
}
