#include "stdafx.h"
#include "TestTemplate.h"
#include "Timer.h"
#include "..\DataStruct.h"
#include <map>
#include <vector>
#include <stdint.h>

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

    const std::vector<TestObject>& refVec = vec;
    RandomPickWeightedIterator(refVec);
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

void TestRandomSplit()
{
    using TT = uint32_t;
    TT total = 200000;
    TT base = 100;
    TT lower = 110;
    int count = 100;
    std::vector<TT> pool;

    timer tmr;
    for (int i = 0; i < 1000; ++i)
    {
        RandomSplitInteger(total, base, lower, count, pool);

        TT sum = 0;
        for (auto p : pool)
        {
            if (p % base != 0 || p < lower)
            {
                std::cout << "bad splited, p: " << p << std::endl;
            }
            sum += p;
        }

        if (sum != total)
        {
            std::cout << "sum is not equal with total, total: " << total << ", sum: " << sum << std::endl;
        }
        else
        {
            /*for (auto p : pool)
            {
            std::cout << p << ", ";
            }
            std::cout << std::endl;*/
        }
    }
    std::cout << "cost time: " << tmr.elapsed() << std::endl;
}

//////////////////////////////////////////////////////////////////////////

//整型序列的定义
template<int...>
struct IndexSeq{};

#if 1

//继承方式，开始展开参数包
template<int N, int ... Indexes>
struct MakeIndexes : MakeIndexes<N - 1, N - 1, Indexes...>{};

//模板特化，终止展开参数包的条件
template<int... Indexes>
struct MakeIndexes<0, Indexes...>
{
    typedef IndexSeq<Indexes...> type;
};

#else

//MakeIndexes如果不通过继承递归方式生成，可以通过using来实现。
template<int N, int ...Indexes>
struct MakeIndexes
{
    using type = MakeIndexes<N - 1, N - 1, Indexes>::type;
};

template<int...Indexes>
struct MakeIndexes<0, ...Indexes>
{
    using type = IndexSeq<Indexes...>;
};

#endif // 0

void TestVariableParamsTemplate()
{
    using T = MakeIndexes<3,5>::type;  //输出为 struct IndexSeq<0,1,2>
    std::cout << typeid(T).name() << std::endl;
};


/*
函数形参列表
在函数形参列表中，若省略号出现于某个形参声明中（无论它是否指名函数形参包（例如在 Args ... args中）），则该形参声明是模式：
*/
template<typename ...Ts, int... N> 
void ppeif(Ts(&...arr)[N]) 
{
    std::cout << sizeof...(arr) << std::endl;
}

void ParamsPacketExpansionInFunction()
{
    int n[1];
    Base b[5];
    ppeif("a", n, b); // Ts (&...arr)[N] 展开成const char (&)[2], int(&)[1]
}

//////////////////////////////////////////////////////////////////////////
void tprintf(const char* format) // 基础函数
{
    std::cout << format;
}

template<typename T, typename... Targs>
void tprintf(const char* format, T value, Targs... Fargs) // 递归变参函数
{
    for (; *format != '\0'; format++) {
        if (*format == '%') {
            std::cout << value;
            tprintf(format + 1, Fargs...); // 递归调用
            return;
        }
        std::cout << *format;
    }
}

//////////////////////////////////////////////////////////////////////////

//#define TEMPLATE_DECLARE_3_SECTION
#define TEMPLATE_DECLARE_2_SECTION

#ifdef TEMPLATE_DECLARE_3_SECTION

//前向声明
template<typename... Args>
struct SumTemplate;

//基本定义
template<typename First, typename... Rest>
struct SumTemplate<First, Rest...>
{
    enum { value = SumTemplate<First>::value + SumTemplate<Rest...>::value };
};

//递归终止
template<typename Last>
struct SumTemplate<Last>
{
    enum { value = sizeof(Last) };
};

#elif defined TEMPLATE_DECLARE_2_SECTION

template<typename First, typename... Rest>
struct SumTemplate
{
    enum { value = SumTemplate<First>::value + SumTemplate<Rest...>::value };
};

template<typename Last>
struct SumTemplate<Last>
{
    enum{ value = sizeof(Last) };
};

#endif // 0

int TestVarParamsInRecursionFuction()
{
    //tprintf("% world% %\n", "Hello", '!', 123);
    std::cout << SumTemplate<char, short, int, double>::value << std::endl;
    return 0;
}



//////////////////////////////////////////////////////////////////////////
template<typename AttrInterval, typename... Args>
class VarParamsClass
{
public:
    static void ParseAttrValue(Args&&... args) {}
};

template<typename AttrInterval, typename XmlElm_t>
class VarParamsClass<AttrInterval, XmlElm_t>
{
public:
    using T = decltype(std::declval<AttrInterval>().GetRandom());
    static void ParseAttrValue(XmlElm_t* sectionXml, const char* attrName){}
    static const std::string& getName() { return name; }
private:
    static const std::string name;
};
template<typename AttrInterval, typename XmlElm_t> const std::string VarParamsClass<AttrInterval, XmlElm_t>::name = "xmlparser";

// 可变参数偏特化
void TestVarParamsPartialSpecialization()
{
    std::cout << VarParamsClass<AttrInterval<int>, Base>::getName().c_str() << std::endl;
}

//////////////////////////////////////////////////////////////////////////
template<int n1, int n2> int CurrencyConvert(int);

template<> int CurrencyConvert<1, 2>(int src)
{
    return src * 2;
}

template<> int CurrencyConvert<1, 3>(int src)
{
    return src * 3;
}

template<> int CurrencyConvert<2, 3>(int src)
{
    return src * 6;
}

template<int n1, int n2> void TempStrComp(const char(&str1)[n1], const char(&str2)[n2])
{
    std::cout << str1 << ", " << n1 << std::endl;
    std::cout << str2 << ", " << n2 << std::endl;
}


void TestTemplateSpecialize()
{
//     template<auto n> struct B { /* ... */ };
//     B<5> b1;   // OK：非类型模板形参类型为 int
//     B<'a'> b2; // OK：非类型模板形参类型为 char
    
    int src = 1;
    std::cout << "CurrencyConvert<1, 2>(1) = " << CurrencyConvert<1, 2>(src) << std::endl;
    std::cout << "CurrencyConvert<1, 3>(1) = " << CurrencyConvert<1, 3>(src) << std::endl;
    std::cout << "CurrencyConvert<2, 3>(1) = " << CurrencyConvert<2, 3>(src) << std::endl;

    TempStrComp("hi", "world");
    TempStrComp("wo", "caoaa");
}

void TestRandomWeightMap()
{
	std::map<int, TestObject> itMap;
	itMap.emplace(std::make_pair(0, TestObject{ 100, 10 }));
	itMap.emplace(std::make_pair(1, TestObject{ 200, 20 }));
	itMap.emplace(std::make_pair(2, TestObject{ 300, 30 }));
	itMap.emplace(std::make_pair(3, TestObject{ 0, 0 }));

	/*auto it = RandomPickWeightedMapIt(itMap);
	if (it != itMap.end())
	{
		std::cout << it->first << ": " << it->second.weight << std::endl;
	}*/
	
	const std::map<int, TestObject>& itMapRef = itMap;
	
	timer tmr;

	int count = 1000000;
	std::map<int, int> selectTimes;
	for (int i = 0; i < count; ++i)
	{
		auto it = RandomPickWeightedMapIt(itMap, 600);
		++selectTimes[it->first];
	}

	std::cout << "cost time: " << tmr.elapsed() << std::endl;
	
	for (const auto& topair : itMap)
	{
		float prob = selectTimes[topair.first] * 1.f / count;
		std::cout << topair.first << " : " << prob << std::endl;
	}	
}
