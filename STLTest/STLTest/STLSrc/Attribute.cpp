#include "stdafx.h"
#include "Attribute.h"
#include <stdint.h>
#include "..\DataStruct.h"

void TestAttrs()
{
    std::string s = "20";
    int v = StringConvert<int>(s);
    std::cout << v << std::endl;

    Base b;
    SectionGroup<SectionAttrs<int>, AttrValueParser<AttrInterval<int>>> intGroup;
    intGroup.ParseNewAttrValue(b, "lower", "upper");
}
