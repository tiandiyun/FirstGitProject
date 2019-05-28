#pragma once

#include <climits>
#include <random>
#include <iostream>
#include <algorithm>
#include "../AutoPtrInherit.h"
#include "Attribute.h"

template <typename DirectAccessContainer, typename DACIterator = DirectAccessContainer::iterator>
DACIterator RandomPickIteratorFromDAC(DirectAccessContainer& ct)
{
    if (ct.empty())
    {
        return ct.end();
    }

    int idx = rand() % (ct.size());

    return ct.begin() + idx;
}

void TestRandomPick();


template<typename WT> struct WeightedObj
{
    WeightedObj() { weight = RWAttrDifference<WT>::Default(); }
    WeightedObj(WT w) : weight(w) {}
    WT weight;
};

template<typename WeightedObjContainer, 
    typename WOCIterator = WeightedObjContainer::iterator, 
    typename WeightedObjRef = decltype(*(std::declval<WOCIterator>())),
    typename WT = decltype(std::declval<WeightedObjRef>().weight)>
WOCIterator RandomPickWeightedIterator(WeightedObjContainer& ct)
{
    if (ct.empty())
    {
        return ct.end();
    }

    WT sum = RWAttrDifference<WT>::Default();
    for_each(ct.begin(), ct.end(), [&sum](WeightedObjRef& obj){ sum += obj.weight; });

    WT markV = RWAttrRandom<WT>::Random(RWAttrDifference<WT>::Default(), sum);
    auto it = ct.begin();
    for (; it != ct.end() && markV > it->weight; markV -= (it++)->weight);

    return it;
}

struct TestObject : public WeightedObj<int>
{
    TestObject(int w, int v) : WeightedObj(w), customV(v){}
    int customV;
};

void TestRandomWeight();

void TestIteratorTraits();

template<typename Container>
void TraversalPrintContainer(Container& ct)
{
    for (auto it = ct.begin(); it != ct.end(); ++it)
    {
        if (it != ct.begin())
        {
            std::cout << ", ";
        }
        std::cout << *it;
    }
    std::cout << std::endl;
}