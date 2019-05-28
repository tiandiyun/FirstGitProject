#include "stdafx.h"
#include "TypeRef.h"
#include <type_traits>
#include "../AutoPtrInherit.h"


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