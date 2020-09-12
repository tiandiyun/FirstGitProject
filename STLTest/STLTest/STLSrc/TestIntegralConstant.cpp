#include "stdafx.h"
#include "TestIntegralConstant.h"
#include <iostream>
#include <type_traits>

void TestIntergral() 
{
    typedef std::integral_constant<int, 1> one_t;
    std::cout << "one_t::value: " << one_t::value << std::endl;
    std::cout << "one_t::type::value: " << one_t::type::value << std::endl;
}