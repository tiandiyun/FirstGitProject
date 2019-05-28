#include "stdafx.h"
#include "TestDeque.h"
#include <iostream>
#include <string>
#include <time.h>
#include "Timer.h"
#include "..\DataStruct.h"

void TestDeque::CompareTraversal()
{
    std::cout << "enter deque capacity" <<std::endl;

    std::deque<int> dq;
    std::string line;
    while (std::getline(std::cin, line))
    {
        int capacity = std::stoi(line);
        for (int i = 0; i < capacity; ++i)
        {
            dq.emplace_back(i);
        }

        TraversalByIndex(dq);
        TraversalByIterator(dq);
        line.clear();
        dq.clear();
    }

}

void TestDeque::TraversalByIndex(std::deque<int>& dq)
{
    timer ts;
    size_t count = dq.size();
    for (size_t i = 0; i < count; ++i)
    {
        if (dq[i] == 10)
        {
        }
    }
    std::cout << "Traversal-By-Index cost time: " << ts.elapsed_millisecond() << std::endl;
}

void TestDeque::TraversalByIterator(std::deque<int>& dq)
{
    timer ts;
    for (auto it = dq.begin(); it != dq.end(); ++it)
    {
        if (*it == 10)
        {
        }
    }
    std::cout << "Traversal-By-Index cost time: " << ts.elapsed_millisecond() << std::endl;
}


void TestDeque::FindIfInDeque()
{
    std::deque<Data> intQ;
    intQ.emplace_back(3);
    intQ.emplace_back(5);
    intQ.emplace_back(4);
    intQ.emplace_back(2);
    intQ.emplace_back(0);

    int i = 0;
    auto it = std::find_if(intQ.begin(), intQ.end(), [&i](const Data& d){
        i++;
        return d.v == 3;
    }
    );
    std::cout << i << std::endl;
}