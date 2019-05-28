#include "stdafx.h"
#include "TestTemplate.h"
#include <vector>


/*
void TestAttribute()
{
    RWAttrBoundaryEX attr;
    std::cout << (int)(attr.LowerLimit()) << ", " << (int)(attr.UpperLimit()) << std::endl;
}*/

void TestRandomPick()
{
    std::vector<int> vec = { 1, 2, 3, 4, 5 };
    auto it = RandomPickIteratorFromDAC<std::vector<int>>(vec);
    std::cout << *it << std::endl;
}

void TestRandomWeight()
{
    std::vector<TestObject> vec;
    vec.emplace_back(0, 100);
    vec.emplace_back(1, 101);
    vec.emplace_back(2, 102);
    vec.emplace_back(3, 103);
    vec.emplace_back(4, 104);
    vec.emplace_back(5, 105);

    ResetSeed();
    RandomPickWeightedIterator(vec);
}

void TestIteratorTraits()
{
    std::vector<int> vec;
    vec.emplace_back(0);
    vec.emplace_back(1);
    vec.emplace_back(2);
    vec.emplace_back(3);
    vec.emplace_back(4);
    vec.emplace_back(5);

    const std::vector<int>& vecRef = vec;

    using ActIterator = decltype(std::declval<const std::vector<int>>().begin());
    using ActRef = decltype(*(std::declval<ActIterator>()));

    using IteratorTraits = std::iterator_traits<decltype(std::declval<decltype(vec)>().begin())>;
    using ConstIteratorTraits = std::iterator_traits<decltype(std::declval<decltype(vecRef)>().begin())>;

    ActIterator ait = vecRef.begin();
    ActRef ar = *ait;

//     IteratorTraits::value_type ittV;
//     ConstIteratorTraits::value_type constIttV;

    std::cout << std::endl;
}
