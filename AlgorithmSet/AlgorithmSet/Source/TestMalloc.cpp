#include "TestMalloc.h"
#include <set>
#include <vector>
#include "../DataModel/SinglyLinkedList.h"
#include "../malloc.h"

static std::set<void*> mmset;
static void* _DLMALLOC(size_t n)
{
	void* p = dlmalloc(n);
	if (p)
		mmset.emplace(p);
	return p;
}

static inline void _DLFREE(void* p)
{
	auto it = mmset.find(p);
	if (it != mmset.end())
	{
		dlfree(p);
		mmset.erase(it);
	}
}

static void _DLFREEALL()
{
	for (auto& p : mmset)
	{
		dlfree(p);
	}
	mmset.clear();
}


void TestMalloc()
{
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
}