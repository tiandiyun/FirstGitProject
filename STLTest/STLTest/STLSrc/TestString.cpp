#include "stdafx.h"
#include "TestString.h"
#include <iostream>
#include <string>


#define _SR_INDEX_MAX (size_t)(-1)


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


    const std::string path = "/root/config";
    pos = path.find_last_of('/');
    auto leaf = path.substr(pos + 1);
    std::cout << leaf << '\n';

    pos = path.find_last_of("\\/66");
    leaf = path.substr(pos + 1);
    std::cout << leaf << '\n';
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

static void ParseSpecialKeys(const std::string& rawStr)
{
	auto pos = rawStr.find(":");
	if (pos == std::string::npos)
	{
		return;
	}

	std::string& key = rawStr.substr(0, pos);
	std::cout << key << " : ";

	int  index = 0;
	int  interFlag = 0;
	auto end = rawStr.length();
	auto prev = pos + 1;
	auto next = prev;
	for (; prev < end; prev = next + 1)
	{
		next = rawStr.find_first_of("[,]", prev);
		if (next != std::string::npos)
		{
			char c = rawStr[next];
			if (c == '[')
			{
				if (interFlag != 0)
				{
					return;
				}

				++interFlag;
			}
			else if (c == ']')
			{
				if (interFlag != 2)
				{
					return;
				}

				++interFlag;
			}
			else
			{
				if (prev == next)
				{
					continue;
				}

				if (interFlag > 1)
				{
					return;
				}

				if (interFlag == 1)
				{
					++interFlag;
				}
			}
		} 
		else
		{
			if (interFlag > 0)
			{
				return;
			}

			next = end;
		}

		if (interFlag == 1)
		{
			continue;
		}

		int value = 0;
		try
		{
			std::string& strv = rawStr.substr(prev, next - prev);
			if (strv == "+")
			{
				value = _SR_INDEX_MAX;
			}
			else
			{
				value = std::stoi(strv);
			}
		}
		catch (std::exception e)
		{
			return;
		}

		if (interFlag == 0 || interFlag == 2)
		{
			index = value;
			std::cout << index << ", ";
		}
		else if (interFlag == 3)
		{
			interFlag = 0;
			int endIdx = value;
			//TODO
			std::cout << "[" << index << ", " << endIdx << "]" << ",";
		}
		else
		{
			return;
		}	
	}

	std::cout << std::endl;
}

void TestParseRedisKey()
{
	const char* SRSpecialKeys[] = {
		"BRPOPLPUSH:0,1",
		"SINTERSTORE:[0,+]",
		"SUNIONSTORE:0, [3,+]"	// TODO: tianyun ÓÐÎÊÌâ
	};

	for (const char* key : SRSpecialKeys)
	{
		ParseSpecialKeys(key);
	}
}