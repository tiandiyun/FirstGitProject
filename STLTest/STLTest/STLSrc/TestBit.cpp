#include "stdafx.h"
#include <iostream>
#include "TestBit.h"


#define ISUNSIGNED(a) ((a) >= 0 && ~(a) >= 0)
#define ISUNSIGNEDTYPE(t) ((t)0 - 1 > 0)
#define IS_UNSIGNED(a) (( (a) |= (0x1 << (sizeof(a)*8 - 1))) > 0 ? 1 : 0 )

void TestOperatorOverFlow()
{
    unsigned short a = 0xffff;
    unsigned short b = 0xfffe;
    unsigned short c = 0x0002;

    if (a < b * c)
    {
        std::cout << "a < b * c" << std::endl;
    }
    else
    {
        std::cout << "a >= b * c" << std::endl;
    }
}

void CheckDataSign()
{
    int a = 10;
    unsigned int b = 10;
    std::cout << "a is unsigned: " << ISUNSIGNED(a) << std::endl;
    std::cout << "b is unsigned: " << ISUNSIGNED(b) << std::endl;

    std::cout << "check signed int sign: " << ISUNSIGNEDTYPE(int) << std::endl;
    std::cout << "check unsigned int sign: " << ISUNSIGNEDTYPE(unsigned int) << std::endl;
}