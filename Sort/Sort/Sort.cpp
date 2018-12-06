// Sort.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include<stdio.h>

int aa[] = { 2, 4, 5, 1, 6, 9, 7, 8, 3 };
// int aa[] = { 5, 4, 6, 9, 7, 8, 3 };

void quickSort(int a[], int left, int right)
{
	if (left >= right)
		return;

	int i = left;
	int j = right;
	int temp = a[left];
	while (i < j)
	{
		while (i < j)
		{
			if (a[j] >= temp)
			{
				--j;
			}
			else
			{
				a[i] = a[j];
				++i;
				break;
			}
		}

		while (i < j)
		{
			if (a[i] <= temp)
			{
				++i;
			}
			else
			{
				a[j] = a[i];
				--j;
				break;
			}
		}	
	}
	a[i] = temp;
	quickSort(a, left, i - 1);
	quickSort(a, i + 1, right);
}

int _tmain(int argc, _TCHAR* argv[])
{
	quickSort(aa, 0, sizeof(aa) / sizeof(aa[0]) - 1);
	getchar();
	return 0;
}

