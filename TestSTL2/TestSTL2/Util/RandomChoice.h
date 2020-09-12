#ifndef _DM_SHARELIB_RANDOM_CHOICE_H_
#define _DM_SHARELIB_RANDOM_CHOICE_H_
#include <assert.h>

int RangeRndI(int beg, int end)
{
    assert(beg <= end);
    return (rand() / (end - beg + 1)) + beg;
}

template<typename WT> struct ObjWithWT
{
    WT weight{ 0 };
};

template<typename WT, typename ObjWithWT, typename ObjContainer>
const ObjWithWT* RandomChoiceObj(const ObjContainer& ct, std::function<WT(WT, WT)> randomWT, WT randMinParam)
{
    WT sumWT = 0;
    for (auto it = ct.begin(); it != ct.end(); ++it)
    {
        sumWT += it->weight;
    }

    WT weight = randomWT(randMinParam, sumWT);
    for (auto it = ct.begin(); it != ct.end(); ++it)
    {
        if (it->weight >= weight)
        {
            return &(*it);
        }

        weight -= it->weight;
    }
    return nullptr;
}


/*template<typename ObjWithWT, typename ObjContainer>
const ObjWithWT* RandomChoiceIntegerWT(const ObjContainer& ct)
{
auto randomFunc = [](int a, int b){ return (MathHelper::RangeRndI(a, b)); };
return RandomChoiceObj<int, DataProbCoeff, ProbCoeffVec>(ct, randomFunc, 1);
}*/

template<typename ObjWithWT, typename ObjContainer>
const ObjWithWT* RandomChoiceUInt32WT(const ObjContainer& ct)
{
    auto randomFunc = [](UINT32 a, UINT32 b){ return (RangeRndI(a, b)); };
    return RandomChoiceObj<UINT32, ObjWithWT, ObjContainer>(ct, randomFunc, 1);
}

/*template<typename ObjWithWT, typename ObjContainer>
const ObjWithWT* RandomChoiceDoubleWT(const ObjContainer& ct)
{
auto randomFunc = [](double a, double b){ return (MathHelper::RangeRndD(a, b)); };
return RandomChoiceObj<double, DataProbCoeff, ProbCoeffVec>(ct, randomFunc, 0);
}*/

#endif // _DM_SHARELIB_RANDOM_CHOICE_H_
