#include "stdafx.h"
#include "TypeRef.h"
#include <type_traits>
#include <vector>
#include <numeric>
#include <random>
#include <iterator>
#include "../DataStruct.h"


void TestDecltype()
{
    Base b;
    //std::cout << "Is b type of Base? " << (typeid(decltype(b)) == typeid(Base) ? "true" : "false") << std::endl;
    std::cout << "Is b type of Base? " << (typeid(b) == typeid(Base) ? "true" : "false") << std::endl;

#ifdef _TA
    std::cout << "_TA" << std::endl;
#elif _TB
    std::cout << "_TB" << std::endl;
#else

#ifdef _TC
    std::cout << "_TC" << std::endl;
#else 
    std::cout << "_NONE" << std::endl;
#endif

#endif
}

class F
{
public:
    int foo();
};

void TestDeclval()
{
    int m = 0;
    using R = int &;

    decltype(std::declval<int>()) a = std::move(m);
    a = 10;

    decltype(std::declval<int&>()) mr = m;
    mr = 1;

    decltype(std::declval<int&>()++) mrAPP = m; //std::declval<R>()++ 表达式的类型为 int
    mrAPP = 2;

    decltype(++std::declval<int&>()) mrBPP = m; //++std::declval<R>() 表达式的类型为int&&
    mrBPP = 3;

    decltype(std::declval<Derive>()) d = Derive();

    decltype(std::declval<F>().foo()) tmp = 0;
}

void TestTypeInfer()
{
    int a = 1, b = 2;
    std::cout << "add(a, b) = " << add(a, b) << std::endl;
    // add("string", "string"); error: no matching function for call to 'add(const char [7], const char [7])'
}

void TestTemplate()
{
    BaseTemplate<int> b;
    b.f = 0.5f;
    std::cout << b.f << std::endl;
}

void TestRefByRef()
{
    int src = 10;
    int& ref1 = src;
    int& ref2 = ref1;
}

void TestRefWrapper()
{
    std::list<int> l(10);
    std::iota(l.begin(), l.end(), -4);

    std::vector<std::reference_wrapper<int>> v(l.begin(), l.end());
    // can't use shuffle on a list (requires random access), but can use it on a vector
    std::shuffle(v.begin(), v.end(), std::mt19937{ std::random_device{}() });

    std::cout << "Contents of the list: ";
    for (int n : l) std::cout << n << ' '; std::cout << '\n';

    std::cout << "Contents of the list, as seen through a shuffled vector: ";
    for (int i : v) std::cout << i << ' '; std::cout << '\n';

    std::cout << "Doubling the values in the initial list...\n";
    for (int& i : l) i *= 2;

    std::cout << "Contents of the list, as seen through a shuffled vector: ";
    for (int i : v) std::cout << i << ' '; std::cout << '\n';
}

struct refWrap
{
    refWrap(int &ii) : i(ii) {}
    std::reference_wrapper<int> i;
};

void TestRefWrapCopy()
{
    std::vector<Base> srcBase;
    for (int i = 0; i < 6; ++i)
    {
        srcBase.emplace_back(Base(i));
    }

    std::cout << "-----------------------" << std::endl;

    std::vector<std::reference_wrapper<Base>> dst2;
    {
        std::vector<std::reference_wrapper<Base>> dst;
        //std::copy(srcBase.begin(), srcBase.end(), std::back_inserter(dst));
        for (auto it = srcBase.begin(); it != srcBase.end(); ++it)
        {
            dst.emplace_back(*it);
        }

        dst2.swap(dst);
    }

    int j = 0;
}

void RefWarpperSort()
{
    std::vector<int> intVec;
    for (int i = 0; i < 6; ++i)
    {
        intVec.emplace_back(6 - 1 - i);
    }

    std::list<std::reference_wrapper<int>> sortList;
    for (auto &d : intVec)
    {
        sortList.emplace_back(d);
    }
    sortList.sort();
}