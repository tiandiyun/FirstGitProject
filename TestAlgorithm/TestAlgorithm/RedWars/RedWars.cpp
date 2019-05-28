#include "stdafx.h"
#include "RedWars.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
#include <list>
#include <set>
#include <algorithm>
#include <assert.h>
#include <windows.h>
#include "../Timer.h"

int RandomRange(int dwMin, int dwMax)
{
    assert(dwMin <= dwMax);

    if (dwMin == dwMax)
    {
        return dwMin;
    }

    std::random_device rd;  // 将用于为随机数引擎获得种子
    std::mt19937 gen(rd()); // 以播种标准 mersenne_twister_engine
    std::uniform_int_distribution<int> dist(dwMin, dwMax);
    return dist(rd);
}

void PrintRPList(const std::list<int>& rpList)
{
    std::cout.setf(std::ios::left);

    int minV = rpList.front();
    int maxV = minV;
    for (int rp : rpList)
    {
        std::cout << std::setw(4) << rp;
        
        if (maxV < rp)
        {
            maxV = rp;
        }

        if (minV > rp)
        {
            minV = rp;
        }
    }

    std::cout << " || " << "min: " << minV << ", max: " << maxV << std::endl;
}

void OutputRPList(const std::list<int>& rpList)
{
    char path[260];
    GetCurrentDirectory(sizeof(path), path);

    std::string patchStr{ path };
    patchStr += "\\RedWarsStat.txt";
    //std::cout << patchStr.c_str() << std::endl;

    std::ofstream ofile;       //定义输出文件
    ofile.open(patchStr, std::ios::app);     //作为输出文件打开
    ofile.flags(std::ios::left);

    for (auto rp : rpList)
    {
        ofile << rp << "\t";
    }
    ofile << std::endl;
}

void ValifyResultList(const std::list<int>& rpList, int srcTotal)
{
    // Valify
    int sum = 0;
    for (int rp : rpList)
    {
        sum += rp;
    }
    assert(sum == srcTotal);
}

void CreateRedPackage(int totalMoney, int divCount)
{
    assert(divCount > 0 && totalMoney >= divCount);

    int minMoney = 1;
    int remain = totalMoney - minMoney * divCount;
    std::list<int> rpList;

    for (int i = 0; i < divCount; ++i)
    {
        int rp;
        
        if (remain > 0 && i != divCount - 1)
        {
            rp = RandomRange(0, remain);
        }
        else
        {
            rp = remain;
        }

        rpList.push_back(rp + minMoney);
        remain -= rp;
    }

    //ValifyResultList(rpList, totalMoney);

    PrintRPList(rpList);
}


void CreateRedPackage2(int totalMoney, int divCount)
{
    assert(divCount > 0 && totalMoney >= divCount);

    int minMoney = 1;
    int remain = totalMoney - minMoney * divCount;
    std::list<int> rpList;

    for (int i = 0; i < divCount; ++i)
    {
        int rp;

        if (remain > 0 && i != divCount - 1)
        {
            int rpMax = remain * 2 / (divCount - i);
            rp = RandomRange(0, rpMax);
        }
        else
        {
            rp = remain;
        }

        rpList.push_back(rp + minMoney);
        remain -= rp;
    }

    //ValifyResultList(rpList, totalMoney);

    PrintRPList(rpList);
}

void CreateRedPackage3(int totalMoney, int divCount)
{
    assert(divCount > 0 && totalMoney > divCount);

    int remain = totalMoney;
    std::set<int> ptSet;
    for (int i = 0; i < divCount - 1; ++i)
    {
        int pt = RandomRange(1, totalMoney - 1);
        while (ptSet.find(pt) != ptSet.end())
        {
            pt = RandomRange(1, totalMoney);
        }
        ptSet.insert(pt);
    }

    std::list<int> rpList;
    int prePt = 0;
    int curPt = 0;
    for (auto it = ptSet.begin(); it != ptSet.end(); ++it)
    {
        curPt = *it;
        rpList.push_back(curPt - prePt);
        prePt = curPt;
    }
    rpList.push_back(totalMoney - curPt);

    //ValifyResultList(rpList, totalMoney);

    //PrintRPList(rpList);

    OutputRPList(rpList);
}


void CreateRedPackage4(int totalMoney, int divCount)
{
    int minMoney = 1;
    assert(divCount > 0 && totalMoney > minMoney * divCount);

    int remain = totalMoney - minMoney * divCount;
    std::list<int> ptList;
    for (int i = 0; i < divCount - 1; ++i)
    {
        int pt = RandomRange(0, remain);
        ptList.emplace_back(pt);
    }
    ptList.sort();

    std::list<int> rpList;
    int prePt = 0;
    int curPt = 0;
    for (auto it = ptList.begin(); it != ptList.end(); ++it)
    {
        curPt = *it;
        rpList.push_back(*it - prePt + minMoney);
        prePt = curPt;
    }
    rpList.push_back(remain - curPt + minMoney);

    //ValifyResultList(rpList, totalMoney);

    //PrintRPList(rpList);

    OutputRPList(rpList);
}

void CompareCrateOrderList(int amount)
{
    std::list<int> numList;
    timer timePreiod;

    // 1. 按顺序排序插入
    timePreiod.restart();
    numList.clear();
    for (int i = 0; i < amount; ++i)
    {
        int t = RandomRange(0, 10000000);
        for (auto it = numList.begin(); it != numList.end(); ++it)
        {
            if (t < *it)
            {
                numList.emplace(it, t);
                break;
            }
        }
        numList.emplace_back(t);
    }
    std::cout << "method 1 cost time: " << timePreiod.elapsed_millisecond() << std::endl;

    // 2. 插入之后再排序
    timePreiod.restart();
    numList.clear();
    for (int i = 0; i < amount; ++i)
    {
        int t = RandomRange(0, 10000000);
        numList.emplace_back(t);
    }
    numList.sort();
    std::cout << "method 1 cost time: " << timePreiod.elapsed_millisecond() << std::endl;
}
