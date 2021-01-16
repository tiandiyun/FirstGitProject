#include <stdlib.h>
#include <iostream>
#include <memory>

struct strc
{
	char a;
	char b[3];
	short c;
};

void TestOperatorOverFlow()
{
    unsigned short a = 0xffff;
    unsigned short b = 0xfffe;
    unsigned short c = 0x0002;

    std::cout << "b * c = " << b * c << std::endl;
    if (a < b * c)
    {
        std::cout << "a < b * c" << std::endl;
    } 
    else
    {
        std::cout << "a >= b * c" << std::endl;
    }
}

class A
{
public:
    virtual ~A() {}

    void Copy(const A& a)
    {
        mData = a.mData;
    }

    virtual void Show()
    {
        std::cout << "A::Show()" << std::endl;
    }

private:
    int mData;
};

class B : public A
{
public:
    virtual void Show()
    {
        std::cout << "B::Show()" << std::endl;
    }
};


int main()
{
	/*std::shared_ptr<A> a = std::make_shared<B>();
    std::shared_ptr<B> b = std::dynamic_pointer_cast<B>(a);
    if (b)
    {
        b->Show();
    }
    else
    {
        std::cout << "b is null" << std::endl;
    }

    a = nullptr;
    b = std::dynamic_pointer_cast<B>(a);
    if (b)
    {
        b->Show();
    }
    else
    {
        std::cout << "b is null" << std::endl;
    }*/

    A* a = nullptr;
    B* b = dynamic_cast<B*>(a);
    if (!b)
    {
        std::cout << "b is null" << std::endl;
    }
    else
    {
        std::cout << "b is not null" << std::endl;
    }
    delete a;

	getchar();

	return 0;
}
