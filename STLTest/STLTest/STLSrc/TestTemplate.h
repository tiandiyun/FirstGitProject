#pragma once

#include <climits>
#include <random>
#include <iostream>
#include <algorithm>
#include <stdint.h>
#include "../AutoPtrInherit.h"
#include "Attribute.h"
#include "CustomRandom.h"

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
    WeightedObj() { weight = AttrDifference<WT>::Default(); }
    WeightedObj(WT w) : weight(w) {}
    WT weight;
};

template<typename WOCIterator,
    typename WeightedObjRef = decltype(*std::declval<WOCIterator>()),
    typename NonConstWeithObj = std::iterator_traits<WOCIterator>::value_type,
    typename NonConstWT = decltype(std::declval<NonConstWeithObj>().weight)
>
WOCIterator RandomPickWeightedIterator(WOCIterator& begIt, WOCIterator& endIt)
{
    if (begIt == endIt)
    {
        return endIt;
    }

    NonConstWT defaultValue = AttrDifference<NonConstWT>::Default();
    NonConstWT sum = defaultValue;
    for_each(begIt, endIt, [&sum](WeightedObjRef obj){ sum += obj.weight; });

    NonConstWT markV = AttrRandom<NonConstWT>::Random(defaultValue + AttrDifference<NonConstWT>::MinDiff(), sum);
    WOCIterator it = begIt;
    for (; it != endIt && markV > it->weight; markV -= (it++)->weight);

    return it;
}

template<typename WeightedObjContainer,
    typename WOCIterator = decltype(std::declval<WeightedObjContainer>().begin())
>
WOCIterator RandomPickWeightedIterator(WeightedObjContainer& ct)
{
    return RandomPickWeightedIterator(ct.begin(), ct.end());
}

template < typename WeightedObjMap,
	typename WOMapIt = decltype(std::declval<WeightedObjMap>().begin()),
	typename WT = decltype(std::declval<WeightedObjMap::mapped_type>().weight)
>
WOMapIt RandomPickWeightedMapIt(WeightedObjMap& wtMap, WT wtSum)
{
	if (wtMap.empty())
	{
		return wtMap.end();
	}

	WT defaultValue = AttrDifference<WT>::Default();
	WT markV = AttrRandom<WT>::Random(defaultValue + AttrDifference<WT>::MinDiff(), wtSum);
	WOMapIt it = wtMap.begin();
	for (; it != wtMap.end() && markV > it->second.weight; markV -= (it++)->second.weight);
	return it;
}

template < typename WeightedObjMap,
	typename WOMapIt = decltype(std::declval<WeightedObjMap>().begin()),
	typename WT = decltype(std::declval<WeightedObjMap::mapped_type>().weight)
>
WOMapIt RandomPickWeightedMapIt(WeightedObjMap& wtMap)
{
	WT wtSum = AttrDifference<WT>::Default();
	for (auto bit = wtMap.begin(); bit != wtMap.end(); ++bit)
	{
		wtSum += bit->second.weight;
	}
	return RandomPickWeightedMapIt(wtMap, wtSum);
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

template<typename SequenceContainer, typename T = SequenceContainer::value_type>
bool RandomSplitInteger(T total, T base, T lower, int count, SequenceContainer& result)
{
    // �������Ƿ�Ϸ�
    if (base <= 0 || count <= 0 || lower < base || total % base != 0)
    {
        return false;
    }

    // ���ֵ���޶�base����ȡ��
    auto floor = ((lower -1) / base + 1) * base;
    if (total < floor * count)
    {
        return false;
    }

    // ��ֵ�۵�����֮�ͣ�Ȼ����Բ�ֻ�������ʣ���ֵ���������֣�
    auto remain = (total - floor * count) / base;

    // ������ɣ�count - 1�����зֵ�
    std::list<int> points;
    for (int i = 0; i < count - 1; ++i)
    {
        T pt = RangeRndI(0, remain);
        points.push_back(pt);
    }
    points.sort();

    // ���յ�ӽ�ȥ����ʼ�з�
    points.push_back(remain);

    // ���зֺ�ÿ��ֵ���ϻ���������
    result.clear();
    int prev = 0;
    for (auto it = points.begin(); it != points.end(); ++it)
    {
        result.push_back((*it - prev) * base + floor);
        prev = *it;
    }
    return true;
}

void TestRandomSplit();

void TestVariableParamsTemplate();

void ParamsPacketExpansionInFunction();

int TestVarParamsInRecursionFuction();

void TestVarParamsPartialSpecialization();

void TestTemplateSpecialize();

void TestRandomWeightMap();