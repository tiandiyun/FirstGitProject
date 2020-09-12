#include "TTBase.h"
#include <iostream>
#include "../Util/UtilFunction.h"

#pragma warning(disable : 4996)

void TestArray()
{
	int a[3][8] = { 0 };
	int* ap = a[0];
	for (int i = 0; i < _ARR_SIZE(a) * _ARR_SIZE(a[0]); *ap++ = i++);
	std::cout << a[2][7] << std::endl;

	//auto aType = decltype(a); 
	auto aTypeName = typeid(a).name();
	std::cout << aTypeName << std::endl;

	int(*p)[8] = a;
	std::cout << int(p + 1) << " - " << int(p) << " = " << (int(p + 1) - int(p)) << std::endl;
}

void TestStrFunc()
{
	/*char string[20] = "Hello there, honey.";
	char* ans;
	ans = strpbrk(string, "aeiou");*/

	/*char str[] = "y129th";
	char accept[] = "1234567890";
	int i = strspn(str, accept);
	printf("str 前 %d 个字符都属于 accept\n", i);

	int ni = strcspn(str, accept);*/

	char str[] = "now # is the time for all # good men to come to the # aid of their country";
	char delims[] = "#!~-_";
	char* result = NULL;
	result = strtok(str, delims);
	while (result != NULL)
	{
		printf("result is \"%s\"\n", result);
		result = strtok(NULL, delims);
	}

	system("pause");
}

void TestFloat()
{
	std::cout << "FLT_RADIX: " << FLT_RADIX << std::endl;
	std::cout << "FLT_MIN_EXP: " << FLT_MIN_EXP << std::endl;
	std::cout << "FLT_MIN: " << FLT_MIN << std::endl;
	std::cout << "FLT_MAX: " << FLT_MAX << std::endl;
	std::cout << "FLT_DIG: " << FLT_DIG << std::endl;
	std::cout << "FLT_MANT_DIG: " << FLT_MANT_DIG << std::endl;
	std::cout << "FLT_ROUNDS: " << FLT_ROUNDS << std::endl;

	/*float f = 12345678.11111;
	printf("%f\n", f);

	float f2 = 0.88889;
	float fSum = f + f2;
	float f3 = 0.1 * 0.1;
	std::cout << f + f2 << std::endl;

	f = 3.1415926;
	std::cout << f << std::endl;

	f = 0 * 0.1;
	std::cout << f << std::endl;*/

	float x = 3.4f, y = -4.3f;
	float z = static_cast<float>(copysign(x, y));
	std::cout << "z = copysign(x, y):  " << z << std::endl;
	std::cout << "logb(8): " << logb(8) << std::endl;
}

void TestAutoAdd()
{
	int a = 0;
	int b = (++a) + (++a) + (++a);
	std::cout << "prep auto add, a: " << a << ", b: " << b << std::endl;

	a = 0;
	b = (a++) + (a++) + (a++);
	std::cout << "post auto add, a: " << a << ", b: " << b << std::endl;
}

