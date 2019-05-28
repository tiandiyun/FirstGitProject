#include "stdafx.h"
#include "LibExport.h"
#include <iostream>

int Sub(int a, int b)
{
    std::cout << a << "-" << b << "=";
    return a - b;
}
