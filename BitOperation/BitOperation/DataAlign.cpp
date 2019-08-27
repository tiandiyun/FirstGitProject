#include "stdafx.h"
#include "DataAlign.h"
#include <iostream>
#include <stddef.h>
#include <type_traits>
#include "../../LibExport/LibExport/Timer.h"

#define PRINTALIGNMODULE(s, d) do \
{ \
    int size = sizeof(s.d); \
    int offset = offsetof(decltype(s), d); \
    std::cout << #d << ", size: " << size << ", offset: " << offset << ", align module: " << (offset % size) << std::endl; \
} while (0)


void ScanStructPadding()
{
    struct MixedData
    {
        char Data1;
        short Data2;
        int Data3;
        char Data4;
    } md;

    std::cout << "[MixedData] Address is " << (int)&md << std::endl;
    std::cout << "[MixedData] Totol size is " << sizeof(MixedData) << std::endl;
    std::cout << "[MixedData] Padding of head is " << (int)&(md.Data1) - (int)(&md) << std::endl;
    std::cout << "[MixedData] Padding of Data2 and Data1 is " << (int)&(md.Data2) - (int)(&(md.Data1) + 1) << std::endl;
    std::cout << "[MixedData] Padding of Data3 and Data2 is " << (int)&(md.Data3) - (int)(&(md.Data2) + 1) << std::endl;
    std::cout << "[MixedData] Padding of Data4 and Data3 is " << (int)&(md.Data4) - (int)(&(md.Data3) + 1) << std::endl;
    std::cout << "[MixedData] Padding of tail is " << (int)(&md + 1) - (int)(&(md.Data4) + 1) << std::endl;


    struct MixedData2
    {
        char Data1;
        short Data2;
        char Data3;
    } md2;

    std::cout << std::endl;
    std::cout << "[MixedData2] Address is " << (int)&md2 << std::endl;
    std::cout << "[MixedData2] Totol size is " << sizeof(MixedData2) << std::endl;
    std::cout << "[MixedData2] Padding of Data2 and Data1 is " << (int)&(md2.Data2) - (int)(&(md2.Data1) + 1) << std::endl;
    std::cout << "[MixedData2] Padding of Data3 and Data2 is " << (int)&(md2.Data3) - (int)(&(md2.Data2) + 1) << std::endl;
    std::cout << "[MixedData2] Padding of tail is " << (int)(&md2 + 1) - (int)(&(md2.Data3) + 1) << std::endl;


    struct MixedData3
    {
        char Data1;
        short Data2;
        long long Data3;
        char Data4;
    } md3;

    std::cout << std::endl;
    std::cout << "[MixedData3] Address is " << (int)&md3 << std::endl;
    std::cout << "[MixedData3] Totol size is " << sizeof(MixedData3) << std::endl;
    std::cout << "[MixedData3] Padding of Data2 and Data1 is " << (int)&(md3.Data2) - (int)(&(md3.Data1) + 1) << std::endl;
    std::cout << "[MixedData3] Padding of Data3 and Data2 is " << (int)&(md3.Data3) - (int)(&(md3.Data2) + 1) << std::endl;
    std::cout << "[MixedData3] Padding of Data4 and Data3 is " << (int)&(md3.Data4) - (int)(&(md3.Data3) + 1) << std::endl;
    std::cout << "[MixedData3] Padding of tail is " << (int)(&md3 + 1) - (int)(&(md3.Data4) + 1) << std::endl;


    struct MixedData4
    {
        short Data1;
        char Data2[3];
    } md4;

    std::cout << std::endl;
    std::cout << "[MixedData4] Address is " << (int)&md4 << std::endl;
    std::cout << "[MixedData4] Totol size is " << sizeof(MixedData4) << std::endl;
    std::cout << "[MixedData4] Padding of Data2 and Data1 is " << (int)&(md4.Data2) - (int)(&(md4.Data1) + 1) << std::endl;
    std::cout << "[MixedData4] Padding of tail is " << (int)(&md4 + 1) - (int)(&(md4.Data2) + 1) << std::endl;


    struct MixedData5
    {
        char Data1[9];
        struct MixedData4 Data2;
    } md5;

    std::cout << std::endl;
    std::cout << "[MixedData5] Address is " << (int)&md5 << std::endl;
    std::cout << "[MixedData5] Totol size is " << sizeof(md5) << std::endl;
    std::cout << "[MixedData5] Padding of Data2 and Data1 is " << (int)&(md5.Data2) - (int)(&(md5.Data1) + 1) << std::endl;
    std::cout << "[MixedData5] Padding of tail is " << (int)(&md5 + 1) - (int)(&(md5.Data2) + 1) << std::endl;

    std::cout << "[MixedData5] Data1 Size: " << sizeof(md5.Data1) << ", Offset: " << offsetof(MixedData5, Data1)
        << ", AlignOf: " << std::alignment_of<decltype(std::declval<MixedData5>().Data1)>::value << std::endl;
    std::cout << "[MixedData5] Data2 Size: " << sizeof(md5.Data2) << ", Offset: " << offsetof(MixedData5, Data2)
        << ", AlignOf: " << std::alignment_of<decltype(std::declval<MixedData5>().Data2)>::value << std::endl;

    /*int srcInt[] = { 0x0, 0x10001 };
    int *alignedPtr = nullptr, *unAlignedPtr = nullptr;

    alignedPtr = &(srcInt[0]);
    unAlignedPtr = (int*)((int)alignedPtr + 2);

    int testCount = 10000000;

    timer tmr;
    for (int i = 0; i < testCount; ++i)
    {
    int temp = *alignedPtr;
    }
    std::cout << "Access aligned data for " << testCount << " times, cost time: " << tmr.elapsed_millisecond() << std::endl;

    tmr.restart();
    for (int i = 0; i < testCount; ++i)
    {
    int temp = *unAlignedPtr;
    }
    std::cout << "Access aligned data for " << testCount << " times, cost time: " << tmr.elapsed_millisecond() << std::endl;*/
}


template<typename T> void PrintDataAlgin(T& t)
{
    int size = sizeof(t);
    int addr = reinterpret_cast<int>(&t);
    std::cout << "type: " << typeid(t).name() << ", size: " << size << ", address: " << addr
        << ", align module: " << (addr % size) << std::endl;
}

void CheckBaseTypeAddr()
{
    char    a;
    short   b;
    int     c;
    float   d;
    double  e;
    long long f;

    PrintDataAlgin(a);
    PrintDataAlgin(b);
    PrintDataAlgin(c);
    PrintDataAlgin(d);
    PrintDataAlgin(e);
    PrintDataAlgin(f);
}


void CheckStructDataOffset()
{
    struct Data
    {
        short       a;
        long long   b;
        float       c;
        int         d;
        char        e;
        double      f;
    } dt;

    PRINTALIGNMODULE(dt, a);
    PRINTALIGNMODULE(dt, b);
    PRINTALIGNMODULE(dt, c);
    PRINTALIGNMODULE(dt, d);
    PRINTALIGNMODULE(dt, e);
    PRINTALIGNMODULE(dt, f);

    Data *pd;
    pd = &dt;
    dt.e = 0;
}



unsigned int size2binidx(size_t _size)
{	/* 8=1000	16=10000	20=10100	24=11000	32=100000	48=110000	4096=1000000000000 */
    unsigned int topbit, size = (unsigned int)(_size >> 4);
    /* 16=1		20=1	24=1	32=10	48=11	64=100	96=110	128=1000	4096=100000000 */

#if defined(__GNUC__)
    topbit = sizeof(size)*__CHAR_BIT__ - 1 - __builtin_clz(size);

#elif defined(_MSC_VER) && _MSC_VER>=1300
    {
        unsigned long bsrTopBit;

        _BitScanReverse(&bsrTopBit, size);

        topbit = bsrTopBit;
    }

#else
    {
        unsigned int x = size;
        x = x | (x >> 1);
        x = x | (x >> 2);
        x = x | (x >> 4);
        x = x | (x >> 8);
        x = x | (x >> 16);
        x = ~x;
        x = x - ((x >> 1) & 0x55555555);
        x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
        x = (x + (x >> 4)) & 0x0F0F0F0F;
        x = x + (x << 8);
        x = x + (x << 16);
        topbit = 31 - (x >> 24);
    }

#endif

    return topbit;
}