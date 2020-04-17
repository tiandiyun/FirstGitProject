#include "MathFuction.h"
#include <iostream>
#include <iomanip>
#include <ios>
#include "TestNumerics.h"

/*
* ���� m * x + n * y = t, m��n��tΪ����
* --> y = (t - mx) / n
* --> ���Ҫ���� y >= 0, ��Ҫ x <= t / m
*/

void DrawFunction()
{
	int m, n, t;
	std::cin >> m >> n >> t;

	int lcm = Lcm(m, n);
	t = t / lcm * lcm;
	std::cout << m << " * x + " << n << " * y = " << t << std::endl;

	int Fx = t / m;
	int Fy = (t - m * Fx) / n;
	std::cout << "Fx: " << Fx << ", Fy: " << Fy << std::endl;
}