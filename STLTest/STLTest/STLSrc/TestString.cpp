#include "stdafx.h"
#include "TestString.h"
#include <iostream>
#include <string>

std::string getStr()
{
	std::string temp = "124432";
	return temp;
}

void TestPCharNullOrEmpty()
{
	const char* pChar = "";
	if (!pChar || strlen(pChar) == 0)
	{
		printf("pChar in null1");
	}

	pChar = nullptr;
	if (!pChar || strlen(pChar) == 0)
	{
		printf("pChar in null2");
	}

	pChar = "a";
	if (!pChar || strlen(pChar) == 0)
	{
		printf("pChar in null3");
	}
}

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

void TestTrimSpace()
{
    std::string tstStr = " ";
    auto index = tstStr.find_first_not_of(" ");
    if (index != std::string::npos)
    {
        tstStr.erase(0, index);
    }

    index = tstStr.find_first_of(" ");
    if (index != std::string::npos)
    {
        tstStr.erase(index);
    }

    std::string tmp;
    int len = tmp.length();
    auto c = tmp[len];
}