#include "SinglyLinkedList.h"


inline SinglyLinkedList::~SinglyLinkedList()
{
	while (mHead)
	{
		LinkedIntNode* node = mHead;
		mHead = node->next;
		delete node;
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

void CheckCircleInSLL(SinglyLinkedList& sll)
{
	LinkedIntNode* prev = sll.Head();
	LinkedIntNode* next = prev;
	while ()
	{

	}
}
