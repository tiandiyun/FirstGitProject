#include "TTStlAlgorithm.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <list>
#include "../Util/UtilFunction.h"

void TestFill()
{
	std::vector <int> V;
	int n, startpos, endpos, paint;

	std::cin >> n;
	V.resize(n);
	while (std::cin >> startpos >> endpos >> paint)
	{
		fill(V.begin() + startpos - 1, V.begin() + endpos, paint);
		for_each(V.begin(), V.end(), [](int& elem) {std::cout << elem << " "; });
		std::cout << std::endl;
	}
}

void TestFillN()
{
	std::vector<int> v1{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	std::fill_n(v1.begin(), 0, -1);

	std::copy(begin(v1), end(v1), std::ostream_iterator<int>(std::cout, ", "));
	std::cout << "\n";
}

void TestContainerInsert()
{
	std::list<int> digits;
	for (int i = 0; i < 5; ++i)
	{
		digits.push_back(i);
	}

	auto it = digits.begin();
	++it;

	digits.insert(it, 9);

	for (int n : digits)
		std::cout << n << ' ';
	std::cout << '\n';
}

void TestEachInserter()
{
	std::vector<int> vecSrc;
	std::list<int> vecDest;

	for (std::vector<int>::size_type i = 0; i < 3; ++i)
	{
		vecSrc.push_back(i);
	}

	copy(vecSrc.begin(), vecSrc.end(), std::back_inserter(vecDest));
	UtilFunction::PrintElements(vecDest);

	copy(vecSrc.begin(), vecSrc.end(), std::front_inserter(vecDest));
	UtilFunction::PrintElements(vecDest);

	copy(vecSrc.begin(), vecSrc.end(), std::inserter(vecDest, ++vecDest.begin()));
	UtilFunction::PrintElements(vecDest);
}

void TestListSort()
{
	std::list<int> numList;
	for (int i = 0; i < 10; ++i)
	{
		numList.push_back(rand() % 10);
	}

	numList.sort([](int l, int r) {
		if (l < r)
		{
			return true;
		}

		return false;

		});
}

void TestInitialize()
{
	//int a[2][3];
	int b[2][3] = { 0 };
	int c[2][3] = { {1, 2, 3} };

	struct sta
	{
		int a;
		int b[3];
	};

	//struct sta sa;
	struct sta sb = { 0 };

	system("pause");
}