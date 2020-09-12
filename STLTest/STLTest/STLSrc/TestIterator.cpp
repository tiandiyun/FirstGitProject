#include "stdafx.h"
#include <vector>
#include <iostream>


void TestReverseIterator()
{
    std::vector<int> intVec;
    for (int i = 0; i < 5; ++i)
    {
        intVec.emplace_back(i);
    }

    std::vector<int>::iterator sIt = intVec.begin() + 3;
    std::vector<int>::reverse_iterator rIt(sIt + 1);
    std::vector<int>::iterator pIt = (rIt + 1).base();
    std::vector<int>::iterator pIt2 = rIt.base() - 1;

    std::cout << "sIt: " << *sIt << std::endl;
    std::cout << "rIt: " << *rIt << std::endl;
    std::cout << "pIt: " << *pIt << std::endl;
    std::cout << "pIt2: " << *pIt2 << std::endl;
}



template <typename T>
class CustomIterator
{
public:
    CustomIterator(T* para, size_t n)
    {
        iter = para + n;
    }

    T& operator*()    //返回类型为指向元素的引用
    {
        return *iter;
    }

    bool operator!=(const CustomIterator& that)
    {
        return this->iter != that.iter;
    }

    CustomIterator& operator++()
    {
        ++iter;
        return *this;
    }

private:
    T* iter;
};

template<typename T>
class CustomContainer
{
public:
    CustomContainer(size_t n) : size(n)
    {
        p = new T[size];
    }

    CustomIterator<T> begin()
    {
        return CustomIterator<T>(this->p, 0);
    }

    CustomIterator<T> end()
    {
        return CustomIterator<T>(this->p, size);
    }

    void print()    //print() 方法用来测试容器的元素
    {
        for (size_t i = 0; i < size; ++i)
        {
            std::cout << p[i] << "  ";
        }
        std::cout << "\n";
    }

private:
    T* p;
    size_t size;
};

void TestCustomIterator()
{
    CustomContainer<int> vec{ 6 };
    int it = 0;
    for (auto& i : vec)
    {
        i = ++it;
    }
    std::cout << "\n";
    vec.print();
}


//////////////////////////////////////////////////////////////////////////
struct node
{
    int index = 0;
    node* next = nullptr;
};

node* CreateNodeList(int len)
{
    node* head = nullptr;
    node* prev = nullptr;
    for (int i = 0; i < len; ++i)
    {
        node* nd = new node();
        nd->index = i;

        if (!head)
        {
            head = nd;
        }

        if (prev)
        {
            prev->next = nd;
        }

        prev = nd;
    }

    return head;
}


template <typename T>
class NodeIterator
{
public:
    NodeIterator(T* nd)
    {
        iter = nd;
    }

    T& operator*()    //返回类型为指向元素的引用
    {
        return *iter;
    }

    bool operator!=(const NodeIterator& that)
    {
        return this->iter != that.iter;
    }

    NodeIterator& operator++()
    {
        iter = iter->next;
        return *this;
    }

private:
    T* iter;
};

class NodeTraverse
{
public:
    NodeTraverse(int len)
    {
        node* prev = nullptr;
        for (int i = 0; i < len; ++i)
        {
            node* nd = new node();
            nd->index = i;

            if (!head)
            {
                head = nd;
            }

            if (prev)
            {
                prev->next = nd;
            }

            prev = nd;
        }
    }

    ~NodeTraverse()
    {
        while (head)
        {
            node* next = head->next;
            delete head;
            head = next;
        }
    }

    NodeIterator<node> begin()
    {
        return NodeIterator<node>(head);
    }

    NodeIterator<node> end()
    {
        return NodeIterator<node>(nullptr);
    }

private:
    node* head;
};


void TestTraversListByIterator()
{
    NodeTraverse trv(10);
    for (auto nd : trv)
    {
        std::cout << nd.index << std::endl;
    }
}