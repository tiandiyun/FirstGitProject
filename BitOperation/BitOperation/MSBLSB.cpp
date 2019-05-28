#include "stdafx.h"
#include "MSBLSB.h"
#include <iostream>
#include <iomanip>
#include <bitset>

// (a + 2^m - 1) & (~(2^m - 1))
#define align4(x) (((((x)-1) >> 2) << 2) + 4)
#define align8(x) (((((x)-1) >> 3) << 3) + 8)

#define alignn(x, n) ((x + n - 1) & (~(n - 1)))

void TraversBit()
{
    int data = 3596480;
    unsigned char *p = reinterpret_cast<unsigned char*>(&data);
    unsigned char *end = p + sizeof(data) / sizeof(unsigned char);
    while (p < end)
    {
        std::cout << std::hex << std::uppercase << std::setw(2) << (unsigned short)*p++ << ",";
    }
    std::cout << std::endl;

    std::cout << std::bitset<sizeof(data) * 8>(data) << std::endl;
    std::cout << std::bitset<sizeof(data) * 8>(data | (-data)) << std::endl;

    std::cout << alignn(37, 10) << std::endl;
}
