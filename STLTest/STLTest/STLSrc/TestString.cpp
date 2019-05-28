#include "stdafx.h"
#include "TestString.h"
#include <iostream>
#include <string>

void TestRFind()
{
    //const char* cfgFile = "../cfg/redWars/redWars.xml";
    //const char* cfgFile = "redWars.xml";
    const char* cfgFile = "redWars";
    //const char* cfgFile = "redWars.xml.xml.xml";
    const char* pStr = cfgFile + strlen(cfgFile) - 1;
    while (pStr >= cfgFile)
    {
        if (*pStr == '\\' || *pStr == '/')
        {
            break;
        }
        --pStr;
    }

    std::string cfgLabel;
    if (pStr >= cfgFile)
    {
        cfgLabel = pStr;
    }
    else
    {
        cfgLabel = cfgFile;
    }

    size_t pos = cfgLabel.rfind('.');
    if (pos != std::string::npos)
    {
        cfgLabel = cfgLabel.substr(0, pos);
    }

    std::cout << cfgLabel.c_str() << std::endl;
}
