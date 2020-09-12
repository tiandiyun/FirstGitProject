#pragma once

#include <list>
#include <typeinfo>
#include <iostream>
#include <string>
#include <stdint.h>
#include "CustomRandom.h"
#include "..\DataStruct.h"

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
template<typename T> class AttrDifference
{
public:
    static T Default() { return static_cast<T>(0); }
    static T MinDiff() { return static_cast<T>(1); }
};

template<> class AttrDifference<float>
{
public:
    static float Default() { return 0.0; }
    static float MinDiff() { return FLT_EPSILON; }
};

template<> class AttrDifference<double>
{
public:
    static double Default() { return 0.0; }
    static double MinDiff() { return DBL_EPSILON; }
};


///////////////////////////////////边界属性///////////////////////////////////////
template<typename T> class AttrBoundary
{
public:
    static T LowerLimit() { return T(); }
    static T UpperLimit() { return T(); }
};

template<> class AttrBoundary<signed char>
{
public:
    static signed char LowerLimit() { return CHAR_MIN; }
    static signed char UpperLimit() { return CHAR_MAX; }
};

template<> class AttrBoundary<unsigned char>
{
public:
    static unsigned char LowerLimit() { return 0; }
    static unsigned char UpperLimit() { return UCHAR_MAX; }
};

template<> class AttrBoundary<short>
{
public:
    static short LowerLimit() { return SHRT_MIN; }
    static short UpperLimit() { return SHRT_MAX; }
};

template<> class AttrBoundary<unsigned short>
{
public:
    static unsigned short LowerLimit() { return 0; }
    static unsigned short UpperLimit() { return USHRT_MAX; }
};

template<> class AttrBoundary<int>
{
public:
    static int LowerLimit() { return INT_MIN; }
    static int UpperLimit() { return INT_MAX; }
};

template<> class AttrBoundary<INT64>
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

template<> class AttrBoundary<UINT64>
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

template<> class AttrBoundary<float>
{
public:
    static float LowerLimit() { return FLT_MIN; }
    static float UpperLimit() { return FLT_MAX; }
};

template<> class AttrBoundary<double>
{
public:
    static double LowerLimit() { return DBL_MIN; }
    static double UpperLimit() { return DBL_MAX; }
};


///////////////////////////////////随机属性///////////////////////////////////////
template<typename T> class AttrRandom
{
public:
    static T Random(T lower, T upper) { return static_cast<T>(RangeRndI(lower, upper)); }
};

template<> class AttrRandom<float>
{
public:
    static float Random(float lower, float upper) { return RangeRndF(lower, upper); }
};

template<> class AttrRandom<double>
{
public:
    static double Random(double lower, double upper) { return RangeRndD(lower, upper); }
};


//////////////////////////////////////////////////////////////////////////

template<typename T> class AttrInterval : public AttrDifference<T>, public AttrBoundary<T>
{
public:
    AttrInterval() { mSecLower = mSecUpper = Default(); }
    AttrInterval(const T &v) : mSecLower(v), mSecUpper(v) {}
    AttrInterval(const T &lower, const T &upper) : mSecLower(lower), mSecUpper(upper) {}

    inline T GetLower() const { return mSecLower; }
    inline T GetUpper() const { return mSecUpper; }
    inline T GetRandom() const { return AttrRandom<T>::Random(mSecLower, mSecUpper); }

    inline void Reset(const T &lower, const T &upper)
    {
        mSecLower = lower;
        mSecUpper = upper;
    }

protected:
    T   mSecLower;
    T   mSecUpper;
};

//////////////////////////////////////////////////////////////////////////

template<typename T> T StringConvert(const std::string& rawString)
{
    T attrValue = AttrDifference<T>::Default();
    //return StrConv::parseVal(rawString, attrValue);
    return static_cast<T>(std::stoi(rawString));
}

template<INT64> INT64 StringConvert(const std::string& rawString)
{ 
    return std::is_same<INT64, long>::value ? std::stol(rawString) : std::stoll(rawString); 
}

template<UINT64> UINT64 StringConvert(const std::string& rawString)
{ 
    return std::is_same<UINT64, unsigned long>::value ? std::stoul(rawString) : std::stoull(rawString); 
}

//////////////////////////////////////////////////////////////////////////

template<typename AttrInterval> class AttrValueParser
{
public:
    using T = decltype(std::declval<AttrInterval>().GetRandom());
    template<typename Base> static void ParseValue(AttrInterval& attr, Base&, const char* lowerName, const char* upperName)
    {
        std::string s = "100";
        std::cout << StringConvert<T>(s) << std::endl;
    }
};

//////////////////////////////////////////////////////////////////////////

template<typename T>
struct SectionAttrs
{
    AttrInterval<T>  keyAttr;
};

template<class SectT, class Parser>
class SectionGroup
{
public:
    using AttrT = decltype(std::declval<SectT>().keyAttr);
    using BaseT = decltype(std::declval<AttrT>().GetRandom());

    template<typename... Args> void  ParseNewAttrValue(Args... args)
    {
        AttrInterval<BaseT> newAttr;
        Parser::ParseValue(newAttr, args...);
    }
};

void TestAttrs();