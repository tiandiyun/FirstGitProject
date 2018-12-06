#ifndef _TEST_BOOST_AUTO_PTR_INHERIT_H_
#define _TEST_BOOST_AUTO_PTR_INHERIT_H_

class Base
{
public:
    Base() : param1(100)
    {
        std::cout << "A()" << std::endl;
    }

    Base(const Base& a) : param1(a.param1)
    {
        std::cout << "A(&)" << std::endl;
    }

    Base& operator=(const Base& a)
    {
        std::cout << "operator=" << std::endl;
        return *this;
    }

    Base(const Base&& a)
    {
        std::cout << "A(const A&& a)" << std::endl;
    }

    Base& operator=(const Base&& a)
    {
        std::cout << "A& operator=(const A&& a)" << std::endl;
        return *this;
    }

    int operator-(const Base& a)
    {
        return 0;
    }

    ~Base()
    {
        std::cout << "~A()" << std::endl;
    }

    Base& Show()
    {
        std::cout << "Show(): " << param1 << std::endl;
        return *this;
    }

    static Base CreateA()
    {
        Base a;
        return a;
    }

    virtual void IMVirturlFunc() {}

private:
    int param1;
};

class Derive : public Base
{
public:
    Derive() : Base() {}
};

void TestAutoPtrInherit();

#endif