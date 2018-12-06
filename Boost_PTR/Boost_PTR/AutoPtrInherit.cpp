#include <iostream> 
#include <typeinfo>
#include <boost/smart_ptr/shared_ptr.hpp>
#include "AutoPtrInherit.h"

void TestAutoPtrInherit()
{
    boost::shared_ptr<Base> ap(new Derive());
    boost::shared_ptr<Derive> bp(new Derive());
    std::cout << "------------------------" << std::endl;

    boost::shared_ptr<Base> tmpA = bp;
    boost::shared_ptr<Derive> pt = boost::dynamic_pointer_cast<Derive>(ap);
    int i = 0;
}



