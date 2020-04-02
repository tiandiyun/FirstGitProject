#include "stdafx.h"
#include "Attribute.h"
#include <stdint.h>


template<typename AttrInterval>
class AttrIntervalParserDerive : public AttrIntervalParser<AttrInterval>
{
protected:
    void ParseAttrValue() override
    {
        std::cout << "Derive Parser" << std::endl;
    }
};

void TestAttrs()
{
    SectionGroup<SectionAttrs<int>> attrGroup;
    attrGroup.PrintBaseType();

    SectionAttrs<int, AttrIntervalParserDerive<AttrInterval<int>>> attrs;
    attrs.keyAttr.Parse();
}
