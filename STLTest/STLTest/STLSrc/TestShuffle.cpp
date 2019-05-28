#include "stdafx.h"
#include "TestShuffle.h"
#include <iostream>
#include <unordered_set>
#include <random>
#include <algorithm>
#include "Timer.h"
#include "CustomRandom.h"
#include "TestTemplate.h"

void ShuffleUnorderedSet()
{
    std::unordered_set<int> iSet;
    iSet.emplace(5);
    iSet.emplace(3);
    iSet.emplace(2);
    iSet.emplace(4);
    iSet.emplace(1);
    iSet.emplace(10);

    std::cout << "Before shuffle: ";
    for (int i : iSet)
    {
        std::cout << i << ", ";
    }
    std::cout << std::endl;

    std::random_device rd;
    std::mt19937 g(rd());
    std::cout << "After shuffle: ";
    for (int i : iSet)
    {
        std::cout << i << std::endl;
    }
}

void ShuffleVectorWithLibrary(int count)
{
    std::vector<int> vec;
    for (int i = 0; i < count; ++i)
    {
        vec.emplace_back(i);
    }
    ResetSeed();

    timer tmr;
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(vec.begin(), vec.end(), g);
    std::cout << "Shuffle vector with library cost time: " << tmr.elapsed() << std::endl;

//     TraversalPrintContainer(vec);
//     std::cout << std::endl;
}

void ShuffleVectorFisherYates(int count)
{
    std::vector<int> vec;
    for (int i = 0; i < count; ++i)
    {
        vec.emplace_back(i);
    }
    ResetSeed();

    timer tmr;
    std::vector<int> newVec;
    while (!vec.empty())
    {
        int j = RangeRndI(0, vec.size() - 1);
        newVec.emplace_back(vec[j]);
        vec.erase(vec.begin() + j);

    }
    std::cout << "Shuffle vector with Fisher-Yates cost time: " << tmr.elapsed() << std::endl;

//     TraversalPrintContainer(newVec);
//     std::cout << std::endl;
}

void ShuffleVectorKnuthDurstenfeld(int count)
{
    std::vector<int> vec;
    for (int i = 0; i < count; ++i)
    {
        vec.emplace_back(i);
    }
    ResetSeed();

    timer tmr;
    size_t vecSize = vec.size();
    for (int i = vecSize - 1; i >= 0; --i)
    {
        int j = RangeRndI(0, i);
        if (j != i)
        {
            std::swap(vec[i], vec[j]);
        }
    }
    std::cout << "Shuffle vector with Knuth-Durstenfeld cost time: " << tmr.elapsed() << std::endl;

//     TraversalPrintContainer(vec);
//     std::cout << std::endl;
}

void ShuffleVectorInsideOut(int count)
{
    std::vector<int> vec;
    for (int i = 0; i < count; ++i)
    {
        vec.emplace_back(i);
    }
    ResetSeed();

    timer tmr;
    std::vector<int> newVec;
    newVec.resize(vec.size());
    newVec[0] = vec[0];

    int vecSize = static_cast<int>(vec.size());
    for (int i = 0; i < vecSize; ++i)
    {
        int j = RangeRndI(0, i);
        newVec[i] = newVec[j];
        newVec[j] = vec[i];
    }
    std::cout << "Shuffle vector with Inside-Out cost time: " << tmr.elapsed() << std::endl;

//     TraversalPrintContainer(newVec);
//     std::cout << std::endl;
}