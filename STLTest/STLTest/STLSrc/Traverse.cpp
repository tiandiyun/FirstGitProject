#include "stdafx.h"
#include "Traverse.h"
#include <list>
#include <vector>
#include <iostream>
#include "Timer.h"

void ListTraverse(int loopCount)
{
    std::list<int> bList;

    for (int i = 0; i < loopCount; ++i)
    {
        bList.emplace_back(i);
    }

    std::cout << "traverse list" << std::endl;

    timer period;
    for (auto& b : bList){}
    std::cout << "traverse based on for-range: " << period.elapsed_millisecond() << std::endl;

    period.restart();
    for (auto it = bList.begin(); it != bList.end(); ++it){}
    std::cout << "traverse based on for-iterator: " << period.elapsed_millisecond() << std::endl;

    /*for (auto ti = bList.begin(); ti != --bList.end(); ++ti)
    {
        auto tti = ti;
        for (; tti != bList.end(); ++tti)
        {
        }
    }*/

}


void VectorTraverse(int loopCount)
{
    std::vector<int> bVect;

    int i = 0;
    bVect.resize(loopCount);
    /*for (auto& b : bVect)
    {
        b = i++;
    }*/

    std::cout << "traverse vector" << std::endl;

    timer period;
    for (auto& b : bVect){}
    std::cout << "traverse based on for-range: " << period.elapsed_millisecond() << std::endl;

    period.restart();
    for (auto it = bVect.begin(); it != bVect.end(); ++it){}
    std::cout << "traverse based on for-iterator: " << period.elapsed_millisecond() << std::endl;
}