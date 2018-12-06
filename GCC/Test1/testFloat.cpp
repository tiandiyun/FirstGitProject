#include <iostream>
#include <algorithm>
#include <string>
#include <stdio.h>
#include <float.h>

int main(int argc, char** argv)
{
	std::cout << "FLT_RADIX: " << FLT_RADIX << std::endl;
    	std::cout << "FLT_MIN_EXP: " << FLT_MIN_EXP << std::endl;
    	std::cout << "FLT_MIN: " << FLT_MIN << std::endl;
    	std::cout << "FLT_MAX: " << FLT_MAX << std::endl;
    	std::cout << "FLT_DIG: " << FLT_DIG << std::endl;
    	std::cout << "FLT_MANT_DIG: " << FLT_MANT_DIG << std::endl;
    	std::cout << "FLT_ROUNDS: " << FLT_ROUNDS << std::endl;


	return EXIT_SUCCESS;
}
