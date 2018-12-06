// Search.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

int aa[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
int target = 11;

int binarySearchLoop(int nums[], int len, int dst)
{
	int l = 0, r = len - 1;
	while (l <= r)
	{
		int mid = (l + r) / 2;
		if (dst > nums[mid])
		{
			l = mid + 1;
		}
		else if (dst < nums[mid])
		{
			r = mid - 1;
		}
		else
		{
			return mid;
		}
	}
	return -1;
}

int binarySearchRecursion(int nums[], int l, int r, int dst)
{
	if (l > r)
		return -1;

	int mid = (l + r) / 2;
	if (dst > nums[mid])
		return binarySearchRecursion(nums, mid + 1, r, dst);
	else if (dst < nums[mid])
		return binarySearchRecursion(nums, l, mid - 1, dst);
	else
		return mid;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int len = sizeof(aa) / sizeof(aa[0]);
	//int idx = binarySearchLoop(aa, len, target);
	int idx = binarySearchRecursion(aa, 0, len - 1, target);
	return 0;
}

