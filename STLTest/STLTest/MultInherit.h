
#include <iostream>


class BC
{
public:
    BC() = default;
    virtual VirtInter() = 0;
};


class DBC1 : virtual public BC
{
    VirtInter() override
    {
        std::cout << "DBC1::VirtInter" << std::endl;
    }
};


class DBC2 : virtual public BC
{
    VirtInter() override
    {
        std::cout << "DBC2::VirtInter" << std::endl;
    }
};


class DDBC : public DBC1, public DBC2
{
    DBC1::VirtInter() override
    {
        std::cout << "DDBC::DBC1::VirtInter" << std::endl;
    }

    DBC2::VirtInter() override
    {
        std::cout << "DDBC::DBC2::VirtInter" << std::endl;
    }
};


void TestDDBC();