#include "stdafx.h"
#include "DataAlign.h"
#include <iostream>
#include "../../LibExport/LibExport/Timer.h"

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
    std::cout << "[MixedData5] Totol size is " << sizeof(MixedData5) << std::endl;
    std::cout << "[MixedData5] Padding of Data2 and Data1 is " << (int)&(md5.Data2) - (int)(&(md5.Data1) + 1) << std::endl;
    std::cout << "[MixedData5] Padding of tail is " << (int)(&md5 + 1) - (int)(&(md5.Data2) + 1) << std::endl;

    
    int srcInt[] = { 0x0, 0x10001 };
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
    std::cout << "Access aligned data for " << testCount << " times, cost time: " << tmr.elapsed_millisecond() << std::endl;
}