#include "stdafx.h"
#include "TestSet.h"
#include <iostream>
#include <set>
#include <unordered_set>
#include <list>
#include <deque>
#include "../DataStruct.h"

void TestUnorderedSet()
{
    std::unordered_set<int> iSet;
    iSet.emplace(5);
    iSet.emplace(3);
    iSet.emplace(2);
    iSet.emplace(4);
    iSet.emplace(1);
    for (int i : iSet)
    {
        std::cout << i << std::endl;
    }

    std::unordered_set<int> tmpSet;
    tmpSet.swap(iSet);
}

void EmplaceToSet()
{
    std::list<Base> bSet;
    Base b;
    bSet.emplace_back(std::move(b));
}

void TraversalEraseSet()
{
    std::set<int> iSet;
    iSet.emplace(5);
    iSet.emplace(3);
    iSet.emplace(2);
    iSet.emplace(4);
    iSet.emplace(1);
    
    auto it = iSet.begin();
    while (it != iSet.end())
    {
        it = iSet.erase(it);
    }
}


void TestSetSort()
{
    class DdzRbtCard
    {
    public:
        DdzRbtCard() = default;
        DdzRbtCard(uint8_t card) : mCardValue(card) {}

        void    SetCard(uint8_t card) { mCardValue = card; }
        uint8_t GetCard() const { return mCardValue; }

        bool    operator<(const DdzRbtCard &otherComb) const { return mCardValue < otherComb.mCardValue; }
    protected:
        uint8_t mCardValue{ 0 };
    };

    // 牌组，对几张牌的组合的抽象，一个牌组属于某一种牌型
    class DdzRbtCardsComb : public DdzRbtCard
    {
    public:
        DdzRbtCardsComb() = default;
        DdzRbtCardsComb(uint8_t cardType, uint8_t keyCard, uint8_t patterLen)
        {
            Reset(cardType, keyCard, patterLen);
        }

        void Reset(uint8_t cardType, uint8_t keyCard, uint8_t patterLen)
        {
            mCardType = cardType;
            mPatternLen = patterLen;
            SetCard(keyCard);
        }

    protected:
        uint8_t     mCardType{ 0 };
        uint8_t     mPatternLen{ 0 };
    };

    std::set<DdzRbtCardsComb> combSet;
    combSet.insert(DdzRbtCardsComb(0, 4, 1));
    combSet.insert(DdzRbtCardsComb(0, 2, 1));
    combSet.insert(DdzRbtCardsComb(0, 8, 1));

    for (const DdzRbtCardsComb &comb : combSet)
    {
        std::cout << (int)comb.GetCard() << std::endl;
    }

    auto begIt = combSet.begin();
    auto endIt = combSet.end();
    std::cout << std::distance(begIt, endIt) << std::endl;
}


void EraseMultSet()
{
    std::set<int> iSet;
    iSet.emplace(5);
    iSet.emplace(3);
    iSet.emplace(2);
    iSet.emplace(4);
    iSet.emplace(1);

    auto it = iSet.begin();
    ++it;

    auto nextIt = std::next(it, 2);
    it = iSet.erase(it, nextIt);
}


