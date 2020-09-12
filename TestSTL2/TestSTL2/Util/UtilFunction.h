#pragma once

#include<iostream>

#define _ARR_SIZE(x) (sizeof(x) / sizeof(x[0]))

class UtilFunction
{
public:
	template<typename T> static void PrintElements(T c)
	{
		for (const auto& d : c)
		{
			std::cout << d << " ";
		}
		std::cout << std::endl;
	}

};