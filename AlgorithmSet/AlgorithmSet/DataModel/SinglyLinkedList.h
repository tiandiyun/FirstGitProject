#pragma once

template<typename T> struct LinkedNode
{
	T	data;
	LinkedNode<T>* next = nullptr;
};

using LinkedIntNode = LinkedNode<int>;


class SinglyLinkedList
{
public:
	SinglyLinkedList() = default;

	~SinglyLinkedList();

	void Append(int d);

	void Remove(int d);

	int  Size() { return mSize; }

	LinkedIntNode* Head() { return mHead; }

	LinkedIntNode* Last() { return mLast; }

private:
	LinkedIntNode*	mHead{ nullptr };
	LinkedIntNode*	mLast{ nullptr };
	int				mSize{ 0 };
};


void TestCreatSinglyList();

bool CheckCircleInSLL();
