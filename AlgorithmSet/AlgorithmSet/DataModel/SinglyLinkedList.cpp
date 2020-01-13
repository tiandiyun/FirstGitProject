#include "SinglyLinkedList.h"


inline SinglyLinkedList::~SinglyLinkedList()
{
	while (mSize > 0)
	{
		LinkedIntNode* node = mHead;
		mHead = node->next;
		delete node;
		--mSize;
	}

	mHead = nullptr;
	mLast = nullptr;
}

void SinglyLinkedList::Append(int d)
{
	LinkedIntNode* node = new LinkedIntNode;
	node->data = d;

	++mSize;
	if (!mHead)
	{
		mHead = node;
		mLast = node;
	}
	else
	{
		mLast->next = node;
		mLast = node;
	}
}

void SinglyLinkedList::Remove(int d)
{
	if (mSize <= 0)
	{
		return;
	}

	LinkedIntNode* node = mHead;
	if (node->data == d)
	{
		mHead = node->next;
		delete node;
		--mSize;
		return;
	}

	while (node->next != nullptr)
	{
		if (node->next->data == d)
		{
			LinkedIntNode* temp = node->next;
			node->next = node->next->next;
			delete temp;

			--mSize;
			break;
		}
		node = node->next;
	}
}

void TestCreatSinglyList()
{
	SinglyLinkedList sll;
	for (int i = 0; i < 100; i++)
	{
		sll.Append(i);
	}

	sll.Remove(0);
	sll.Remove(50);
	sll.Remove(99);
	sll.Remove(100);
}

bool CheckCircleInSLL()
{
	// 创建带环的单向链表
	SinglyLinkedList sll;
	int count = 100;
	for (int i = 0; i < count; i++)
	{
		sll.Append(i);
	}
	LinkedIntNode* linkNode = sll.Last();

	for (int i = count; i < count + 49; i++)
	{
		sll.Append(i);
	}
	sll.Last()->next = linkNode->next;

	/*
		D是无环长度，S是环长度
		T = D + (S - D mod S) mod S
	*/

	// 检测环是否存在
	int checkStep = 0;
	LinkedIntNode* prv = sll.Head();
	LinkedIntNode* nxt = prv;
	while (nxt && nxt->next)
	{
		++checkStep;
		prv = prv->next;
		nxt = nxt->next->next;
		if (prv == nxt)
		{
			return true;
		}
	}

	return false;
}
