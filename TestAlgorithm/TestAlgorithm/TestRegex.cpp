#include "stdafx.h"
#include <iostream>
#include <regex>

void TestRegexSearch()
{
    // HTTP/1.1 200 OK
    std::regex reg("HTTP/.+\\s+(\\d+?)\\s+([A-Za-z]+).*");
    std::cmatch match;
    auto ret = std::regex_search("HTTP/1.1 200 OK", match, reg);
    if (ret)
    {
        for (auto& elem : match)
            std::cout << elem << std::endl;
    }
}