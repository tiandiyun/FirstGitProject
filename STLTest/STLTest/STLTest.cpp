// STLTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include "DataStruct.h"
#include "TestMove.h"
#include "AutoPtrInherit.h"
#include "STLSrc/TestDeque.h"
#include "STLSrc/TypeRef.h"
#include "STLSrc/Traverse.h"
#include "STLSrc/TestTemplate.h"
#include "STLSrc/TestC11Time.h"
#include "STLSrc/TestSet.h"
#include "STLSrc/TestVector.h"
#include "STLSrc/TestShuffle.h"
#include "STLSrc/TestString.h"
#include "STLSrc/TestSharePtr.h"
#include "STLSrc/TemplateSpecialization.h"
#include "STLSrc/TestMap.h"
#include "STLSrc/TestTuple.h"
#include "STLSrc/TestException.h"
#include "STLSrc/TestVirtualFunc.h"
#include "STLSrc/TestIterator.h"
#include "STLSrc/TestBit.h"
#include "STLSrc/Attribute.h"


class b
{
public:
    virtual void haha() = 0;
};

class db : public b
{

public:
    virtual void haha() override
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

};

int _tmain(int argc, _TCHAR* argv[])
{
    TestEmplaceVector();

    system("pause");
    return 0;
}

