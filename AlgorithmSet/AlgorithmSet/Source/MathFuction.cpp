#include "MathFuction.h"
#include <iostream>
#include <iomanip>
#include <ios>
#include "TestNumerics.h"

/*
* 函数 m * x + n * y = t, m、n和t为常数
* --> y = (t - mx) / n
* --> 如果要满足 y >= 0, 需要 x <= t / m
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