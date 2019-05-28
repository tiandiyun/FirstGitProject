#pragma once

#include <deque>


class TestDeque
{
public:

    static void CompareTraversal();

    static void TraversalByIndex(std::deque<int>& dq);

    static void TraversalByIterator(std::deque<int>& dq);

    static void FindIfInDeque();;
};
