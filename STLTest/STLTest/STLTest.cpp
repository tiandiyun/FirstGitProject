// STLTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <list>
#include <set>
#include <vector>
#include <deque>
#include <algorithm>
#include <cstdio>
#include <stdio.h>
#include "DataStruct.h"
#include "TestMove.h"
#include "AutoPtrInherit.h"
#include "STLSrc/TestDeque.h"
#include "STLSrc/TypeRef.h"
#include "STLSrc/Traverse.h"
#include "STLSrc/TestTemplate.h"
#include "STLSrc/TestC11Time.h"
#include "STLSrc/TestSet.h"
#include "STLSrc/TestVector.h"
#include "STLSrc/TestShuffle.h"
#include "STLSrc/TestString.h"


std::string getStr()
{
    std::string temp = "124432";
    return temp;
}

Fish getFish()
{
    Fish f;
    return f;
}

void useFish(Fish& f)
{
    int i = 0;
}

void TestStoreStructWithString()
{
    Fish fs;
    fs.id = 10;
    fs.kind = 20;
    fs.leftSeconds = 30;
    fs.type = 40;
    fs.leftSeconds = 50;

    std::string dstStr((char*)&fs, sizeof(fs));
    if (dstStr.size() == sizeof(fs))
    {
        Fish ffs;
        memcpy(&ffs, dstStr.c_str(), dstStr.size());
        int i = 0;
    }
}

void printAll(int i1, int i2)
{
    std::cout << i1 << ", " << i2 << std::endl;
}

void TestPCharNullOrEmpty()
{
    const char* pChar = "";
    if (!pChar || strlen(pChar) == 0)
    {
        printf("pChar in null1");
    }

    pChar = nullptr;
    if (!pChar || strlen(pChar) == 0)
    {
        printf("pChar in null2");
    }

    pChar = "a";
    if (!pChar || strlen(pChar) == 0)
    {
        printf("pChar in null3");
    }
}

void TestMapAccess()
{
    std::map<int, int> data;
    data[0] = 0;
    data[1] = 1;
    data[2] = 2;

    auto it = data.find(0);
    if (it != data.end())
    {
        it->second += 3;
    }

    for (auto& d : data)
    {
        d.second += 2;
    }

    for_each(data.begin(), data.end(), [](std::pair<int, int> dataPair) { std::cout << dataPair.first << ", " << dataPair.second << std::endl; });

    /*auto it = data.begin();
    while (it != data.end())
    {
    it = data.erase(it);
    }*/
}

void TestMapCopy()
{
    std::map<int, int> srcMap;
    srcMap[0] = 0;
    srcMap[1] = 1;
    srcMap[2] = 2;

    std::map<int, int> dstMap = srcMap;
    dstMap[0] = 5;
    dstMap[2] = 7;
}

void TestMapEmplace()
{
    std::map<int, std::map<int, Fish>> playerFishMap;
    std::map<int, Fish> fishMap;
    /*fishMap[0];
    fishMap[1] = Fish();*/
    fishMap.insert(std::make_pair(1, Fish()));
    std::cout << "-----------------------" << std::endl;
    fishMap.emplace(2, Fish());
    //playerFishMap[0] = fishMap;

    //std::map<int, std::string> m{ { 0, "t" } };
}

void TestVectorEmplace()
{
    std::vector<Fish> fishVec;
    fishVec.emplace_back(Fish());
    fishVec.emplace_back(Fish());
    for (auto fishData : fishVec)
    {
        int i = 0;
    }

    fishVec.clear();
    for (int i = 0; i < 3; ++i)
    {
        fishVec.emplace(fishVec.begin(), Fish());
        std::cout << "-------------" << std::endl;
    }
}

void TestMultiMap()
{
    std::multimap<char, int> mymm;

    mymm.insert(std::make_pair('x', 10));
    mymm.insert(std::make_pair('y', 20));
    mymm.insert(std::make_pair('z', 30));
    mymm.insert(std::make_pair('z', 40));
    mymm.insert(std::make_pair('a', 60));

    std::multimap<char, int>::iterator it = mymm.find('x');
    auto v = *it;

    std::multimap<char, int>::iterator itz = mymm.find('z');
    auto vz = *itz;

    std::multimap<char, int>::size_type size = mymm.count('z');

    for (std::multimap<char, int>::iterator ittemp = itz; ittemp != mymm.end(); ++ittemp)
    {
        std::cout << (*ittemp).second << std::endl;
    }
}

void TestSet()
{
    std::set<int> intSet;
    intSet.clear();

    intSet.insert(4);
    intSet.insert(3);
    intSet.insert(2);
    intSet.insert(1);

    for (int a : intSet)
    {
        std::cout << a << std::endl;
    }

    int data = intSet.erase(3);
    std::cout << data << std::endl;

    data = intSet.erase(2);
    std::cout << data << std::endl;

    auto d = intSet.find(4);
}

void TestAlign()
{
    std::cout << sizeof(DataTestAlign) << std::endl;
    //std::cout << sizeof(DataTestAlignEx) << std::endl;
}

void TestStringCopyConstruct()
{
    char src[10];
    memset(src, 0, sizeof(src));

    std::string dstStr(src, sizeof(src));
    std::cout << dstStr.size() << std::endl;
}

void TestScanf()
{
    char buf[512] = { 0 };
    sscanf_s("hello, world", "%*s%s", buf, sizeof(buf) - 1);
    printf("%s\n", buf);

    char sztime1[16] = "", sztime2[16] = "";
    sscanf_s("2006:03:18  -   2006:04:18", "%s - %s", sztime1, sizeof(sztime1) - 1, sztime2, sizeof(sztime2) - 1);
}

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


void TestStaticLocalVariable1()
{
    static int a = 1;
    std::cout << "&a : " << std::ios::hex << &a << ", a = " << std::ios::dec << a << std::endl;
}

void TestStaticLocalVariable2()
{
    static int a = 2;
    std::cout << "&a : " << std::ios::hex << &a << ", a = " << std::ios::dec << a << std::endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
    //std::string& st = getStr();

    //Fish* fs = new Fish(){1, 2, 3, 4, 5.f};

    //useFish(getFish());

    //TestMapAccess();

    //TestAlign();

    //TestGetAutoPointer();

    //TestMoveString();

    //TestFindIf();

    //TestSet();

    //TestVecEmplace();

    //TestListEmplace();

    //BasePtrToDerive();

    //TestDeque::CompareTraversal();

    //TestOperatorOverFlow();

    //TestDecltype();

    //TestDeclval();

    //TestTypeInfer();

    //ListTraverse(100);
    //VectorTraverse(100);

    //TestSection();

    //TestTemplate();

    //TestRep();

    //TestUnorderedSet();

    //EmplaceToSet();

    //TestAttribute();

    //TestRandomPick();

    //TestRandomWeight();

    //TestIteratorTraits();

    //TestFindIfInVector();

    //ShuffleUnorderedSet();

    /*int count = 100000;

    ShuffleVectorWithLibrary(count);

    ShuffleVectorFisherYates(count);

    ShuffleVectorKnuthDurstenfeld(count);

    ShuffleVectorInsideOut(count);*/

    /*TestStaticLocalVariable1();
    TestStaticLocalVariable2();*/

    // TraversalEraseSet();
    
    /*char * const * (*next)(int, int(*)(char, short)) = nullptr;

    //void(int) * signal(int sig, void(*func)(int));
    void(*signal(int sig, void(*func)(int)))(int);*/

    //std::cout << ExtVal2 << std::endl;

    

    system("pause");

    return 0;
}

