#include "stdafx.h"
#include "TestException.h"
#include <stdexcept>

void ThrowExcept()
{
    throw std::logic_error("custom error !");
}
