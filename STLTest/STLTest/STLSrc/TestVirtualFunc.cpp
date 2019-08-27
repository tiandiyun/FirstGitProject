#include "stdafx.h"
#include "TestVirtualFunc.h"
#include <iostream>

BaseCls::BaseCls()
{
    this->Init();
}

void BaseCls::Init()
{
    std::cout << "BaseCls::Init" << std::endl;
}

DeriveCls::DeriveCls() : BaseCls()
{

}

void DeriveCls::Init()
{
    std::cout << "DeriveCls::Init" << std::endl;
}
