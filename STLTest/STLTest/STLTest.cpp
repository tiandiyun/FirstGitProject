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

#include "DataStruct.h"
#include "TestMove.h"

std::string getStr()
{
    std::string temp = "124432";
    return temp;
}

/*
struct Fish
{
Fish(int _id, int _type, int _kind, int _worth, float _ls)
: id(_id), type(_type), kind(_kind), worth(_worth), leftSeconds(_ls)
{
std::cout << "use initialize-list contruct" << std::endl;
}
int id{ 0 };
int type{ 0 }; // 类型
int kind{ 0 }; // 种类
int worth{ 0 }; // 倍数
float leftSeconds{ 0.0f }; // 剩余存活时间
};*/

struct Fish
{
    Fish()
    {
        std::cout << "Fish()" << std::endl;
    }

    Fish(const Fish& fish)
    {
        id = fish.id;
        type = fish.type;
        kind = fish.kind;
        worth = fish.worth;
        std::cout << "Fish(const Fish& fish)" << std::endl;
    }

    Fish(int i, int t, int k, int w, float s)
        : id(i), type(t), kind(k), worth(w), leftSeconds(s)
    {
        std::cout << "Fish(int i, int t, int k, int w, float s)" << std::endl;
    }

    Fish& operator=(const Fish& fish)
    {
        id = fish.id;
        type = fish.type;
        kind = fish.kind;
        worth = fish.worth;
        std::cout << "operator=" << std::endl;
        return *this;
    };

    Fish& operator +=(const Fish& other)
    {
        worth += other.worth;
        return *this;
    }

    Fish operator +(const Fish& other)
    {
        Fish tempFish = *this;
        tempFish.worth += other.worth;
        return tempFish;
    }

    ~Fish()
    {
        std::cout << "~Fish()" << std::endl;
    }

    Fish& operator()()
    {
        return *this;
    }

    int id{ 1 };
    int type{ 2 }; // 类型
    int kind{ 3 }; // 种类
    int worth{ 4 }; // 倍数
    float leftSeconds{ 5.f }; // 剩余存活时间
};

typedef std::shared_ptr<Fish> FishPtr;
typedef std::list<FishPtr> FishList;

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

void TestSharePtrInSTL()
{
    FishList fishes;
    for (int i = 0; i < 5; ++i)
    {
        fishes.push_back(FishPtr(new Fish()));
    }

    for (FishPtr& fish : fishes)
    {
        Fish& fs = *fish;
        int id = fish->id;
        printf("%d", id);
    }

    std::map<int, Fish> fishMap;
    Fish f;
    fishMap[0] = f;
}

int get1()
{
    return 1;
}

int get2()
{
    return 2;
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
    
    for (auto& d: data)
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
    std::set<int> setInteger;
    setInteger.clear();

    setInteger.insert(1);
    setInteger.insert(2);
    setInteger.insert(1);

    for (int a : setInteger)
    {
        std::cout << a << std::endl;
    }
}

void TestListEmplace()
{
    std::list<Fish> fishList;
    Fish fs;
    fs.id = 10;
    fs.kind = 20;
    fs.leftSeconds = 30;
    fs.type = 40;
    fs.leftSeconds = 50;
    //fishList.emplace_back(fs);
    fishList.push_front(fs);
    std::cout << "-------------" << std::endl;
    fishList.pop_back();

    for (int i = 0; i < 10; ++i)
    {
        fishList.push_back(Fish());
    }

    std::list<Fish>::iterator it = fishList.begin();
}

void TestDQueueAndVectorEmplace()
{
    std::deque<int> intDQ;
    for (int i = 0; i < 10; ++i)
    {
        intDQ.emplace_front(i);
    }
    for_each(intDQ.begin(), intDQ.end(), [](int i){ std::cout << i << ","; });
    std::cout << std::endl;

    std::vector<int> intVec;
    for (int i = 0; i < 10; ++i)
    {
        intVec.emplace(intVec.begin(), i);
    }
    //for_each(intVec.begin(), intVec.end(), [](int i){ std::cout << i << ","; });
    for (auto i : intVec)
    {
        std::cout << i << ",";
    }
    std::cout << std::endl;
}

void TestRefByRef()
{
    int src = 10;
    int& ref1 = src;
    int& ref2 = ref1;
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

class TestGun
{
public:
    TestGun()
    {
        pp = new char[30];
        strcpy_s(pp, 30, "hahah");
    }

    ~TestGun()
    {
        if (pp)
        {
            delete[] pp;
        }
    }

    char* getCH()
    {
        return pp;
    }

public:
    char* pp{ nullptr };
};

void TestGetAutoPointer()
{
    TestGun gun;
    const auto gp = gun.getCH();
    auto gpp = gun.getCH();
}

int _tmain(int argc, _TCHAR* argv[])
{
    //std::string& st = getStr();

    //Fish* fs = new Fish(){1, 2, 3, 4, 5.f};

    //useFish(getFish());

    //printAll(get1(), get2());

    //TestMapAccess();

    //TestAlign();

    //TestGetAutoPointer();

    TestMoveString();

    system("pause");

    return 0;
}

