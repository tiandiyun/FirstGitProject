#include "stdafx.h"
#include "CustomRandom.h"
#include <random>
#include <time.h>
#include <stdint.h>

static std::mt19937 rgn;

void ResetSeed()
{
    rgn.seed((unsigned int)time(NULL));
}

int RangeRndI(int dwMin, int dwMax)
{
    if (dwMin >= dwMax)
        return dwMin;
    std::uniform_int_distribution<int32_t> ui(dwMin, dwMax);
    return ui(rgn);
}

float RangeRndF(float fMin, float fMax)
{
    if (fMin >= fMax)
        return fMin;
    std::uniform_real_distribution<float> ur(fMin, fMax);
    return ur(rgn);
}

double RangeRndD(double dMin, double dMax)
{
    if (dMin >= dMax)
        return dMin;
    std::uniform_real_distribution<double> ur(dMin, dMax);
    return ur(rgn);
}