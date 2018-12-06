#include "c.h"
#include "a.h"
/*#include "b.cpp"*/

void PrintB();

void PrintC()
{
	PrintB();
	printf("this is PrintC()\n");
	a = 3;
}

