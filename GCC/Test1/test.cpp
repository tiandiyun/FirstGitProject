#include <stdlib.h>
#include <iostream>

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


int main()
{
	
	//std::cout << sizeof(strc) << std::endl;
	
    	//TestOperatorOverFlow();

	bool flag = false;
	std::cout << flag << std::endl;

	getchar();

	return 0;
}
