//#include <stdlib>
#include <iostream>

struct strc
{
	char a;
	char b[3];
	short c;
};

int main()
{
	std::cout << sizeof(strc) << std::endl;
	
	getchar();
	return 0;
}
