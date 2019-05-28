#pragma once

#include "CustomRandom.h"

#ifdef _WIN64
typedef long INT64;
typedef unsigned long UINT64;
#elif _WIN32
typedef long long INT64;
typedef unsigned long long UINT64;
#else 
#   ifdef __x86_64__
typedef long INT64;
typedef unsigned long UINT64;
#   else
typedef long long INT64;
typedef unsigned long long UINT64;
#   endif
#endif

///////////////////////////////////差值属性///////////////////////////////////////
template<typename T> class RWAttrDifference
{
public:
    static T Default() { return static_cast<T>(0); }
    static T MinDiff() { return static_cast<T>(1); }
};

template<> class RWAttrDifference<float>
{
public:
    static float Default() { return 0.0; }
    static float MinDiff() { return FLT_EPSILON; }
};

template<> class RWAttrDifference<double>
{
public:
    static double Default() { return 0.0; }
    static double MinDiff() { return DBL_EPSILON; }
};


///////////////////////////////////边界属性///////////////////////////////////////
template<typename T> class RWAttrBoundary
{
public:
    static T LowerLimit() { return T(); }
    static T UpperLimit() { return T(); }
};

template<> class RWAttrBoundary<signed char>
{
public:
    static signed char LowerLimit() { return CHAR_MIN; }
    static signed char UpperLimit() { return CHAR_MAX; }
};

template<> class RWAttrBoundary<unsigned char>
{
public:
    static unsigned char LowerLimit() { return 0; }
    static unsigned char UpperLimit() { return UCHAR_MAX; }
};

template<> class RWAttrBoundary<short>
{
public:
    static short LowerLimit() { return SHRT_MIN; }
    static short UpperLimit() { return SHRT_MAX; }
};

template<> class RWAttrBoundary<unsigned short>
{
public:
    static unsigned short LowerLimit() { return 0; }
    static unsigned short UpperLimit() { return USHRT_MAX; }
};

template<> class RWAttrBoundary<int>
{
public:
    static int LowerLimit() { return INT_MIN; }
    static int UpperLimit() { return INT_MAX; }
};

template<> class RWAttrBoundary<INT64>
{
public:
    static INT64 LowerLimit()
    {
#ifdef _WIN64
        return LONG_MIN;
#elif defined _WIN32
        return LLONG_MIN;
#elif defined __x86_64__
        return LONG_MIN;
#else
        return LLONG_MIN;
#endif
    }

    static INT64 UpperLimit()
    {
#ifdef _WIN64
        return LONG_MAX;
#elif defined _WIN32
        return LLONG_MAX;
#elif defined __x86_64__
        return LONG_MAX;
#else
        return LLONG_MAX;
#endif 
    }
};

template<> class RWAttrBoundary<UINT64>
{
public:
    static UINT64 LowerLimit() { return 0; }

    static UINT64 UpperLimit()
    {
#ifdef _WIN64
        return ULONG_MAX;
#elif defined _WIN32
        return ULLONG_MAX;
#elif defined __x86_64__
        return ULONG_MAX;
#else
        return ULLONG_MAX;
#endif
    }
};

template<> class RWAttrBoundary<float>
{
public:
    static float LowerLimit() { return FLT_MIN; }
    static float UpperLimit() { return FLT_MAX; }
};

template<> class RWAttrBoundary<double>
{
public:
    static double LowerLimit() { return DBL_MIN; }
    static double UpperLimit() { return DBL_MAX; }
};


///////////////////////////////////随机属性///////////////////////////////////////
template<typename T> class RWAttrRandom
{
public:
    static T Random(T lower, T upper) { return static_cast<T>(RangeRndI(lower, upper)); }
};

template<> class RWAttrRandom<float>
{
public:
    static float Random(float lower, float upper) { return RangeRndF(lower, upper); }
};

template<> class RWAttrRandom<double>
{
public:
    static double Random(double lower, double upper) { return RangeRndD(lower, upper); }
};