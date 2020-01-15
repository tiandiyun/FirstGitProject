// AlgorithmSet.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <memory>
#include <set>
#include <windows.h>
#include "DataModel/SinglyLinkedList.h"
#include "malloc.h"

static std::set<void*> mmset;
inline void* _DLMALLOC(size_t n)
{
	void* p = dlmalloc(n);
	if (p)
		mmset.emplace(p);
	return p;
}

inline void _DLFREE(void* p)
{
	auto it = mmset.find(p);
	if (it != mmset.end())
	{
		dlfree(p);
		mmset.erase(it);
	}
}

void _DLFREEALL()
{
	for (auto& p : mmset)
	{
		dlfree(p);
	}
	mmset.clear();
}

//////////////////////////////////////////////////////////////////////
//#define NTREEBINS			(32U)
//#define TREEBIN_SHIFT		(8U)
//#define SIZE_T_BITSIZE      (sizeof(size_t) << 3)
//#define SIZE_T_ONE          ((size_t)1)
//typedef unsigned int		bindex_t;         /* Described below */
//
//#define compute_tree_idx(S, I)\
//{\
//  size_t X = S >> TREEBIN_SHIFT;\
//  if (X == 0)\
//    I = 0;\
//  else if (X > 0xFFFF)\
//    I = NTREEBINS-1;\
//  else {\
//    unsigned int K;\
//    _BitScanReverse((DWORD *) &K, (DWORD) X);\
//    I =  (bindex_t)((K << 1) + ((S >> (K + (TREEBIN_SHIFT-1)) & 1)));\
//  }\
//}
//
//#define leftshift_for_tree_idx(i) \
//   ((i == NTREEBINS-1)? 0 : \
//    ((SIZE_T_BITSIZE-SIZE_T_ONE) - (((i) >> 1) + TREEBIN_SHIFT - 2)))
////////////////////////////////////////////////////////////////////////


int main()
{
	/*{
		unsigned long index;
		_BitScanReverse(&index, 2u);
		std::cout << index << std::endl;
		return 0;
	}*/


	/*{
		size_t mem = 1926;
		size_t idx = 0;
		compute_tree_idx(mem, idx);
		auto sizebits = leftshift_for_tree_idx(idx);
		return 0;
	}*/


	auto p0 = _DLMALLOC(5);
	auto p1 = _DLMALLOC(14);
	auto p2 = _DLMALLOC(19);
	auto p3 = _DLMALLOC(23);
	auto p4 = _DLMALLOC(60);
	auto p5 = _DLMALLOC(63);
	auto p6 = _DLMALLOC(100);
	auto p7 = _DLMALLOC(102);
	auto p8 = _DLMALLOC(223);
	auto p9 = _DLMALLOC(216);

	_DLFREE(p1);
	_DLFREE(p3);
	_DLFREE(p5);
	_DLFREE(p7);
	_DLFREE(p8);

	_DLMALLOC(8);
	_DLMALLOC(20);
	_DLMALLOC(16);

	auto t0 = _DLMALLOC(266);
	auto t1 = _DLMALLOC(378);
	auto t2 = _DLMALLOC(612);
	auto t3 = _DLMALLOC(789);

	_DLFREEALL();

	system("pause");
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
