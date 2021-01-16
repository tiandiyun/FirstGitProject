#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <regex>
#include "TestRegex.h"

void TestRegexSearch()
{
	// HTTP/1.1 200 OK
	std::regex reg("HTTP/.+\\s+(\\d+?)\\s+([A-Za-z]+).*");
	std::cmatch match;
	auto ret = std::regex_search("HTTP/1.1 200 OK", match, reg);
	if (ret)
	{
		for (auto& elem : match)
		{
			std::cout << elem << std::endl;
		}
	}
}

void TestRegexMatch()
{
	std::smatch smtch;
	std::string endPattern = ".*a.+\\d{1,2}$";
	std::string rawStr = "ddac4";
	auto ret = std::regex_match(rawStr, smtch, std::regex(endPattern));
	if (ret)
	{
		for (auto& elem : smtch)
			std::cout << elem << std::endl;
	}


	const char* dtpt = "\\d{1,4}-\\d{1,2}-\\d{1,2}";
	const char* dupt = "\\d{1,2}(:\\d{1,2}){0,1}(:\\d{1,2}){0,1}";
	std::stringstream pattern;
	std::cmatch match;

	pattern.str("");
	pattern << "^" << dtpt << "$";
	ret = std::regex_match("2008-5-6", match, std::regex(pattern.str()));
	if (ret)
	{
		for (auto& elem : match)
			std::cout << elem << std::endl;
	}

	pattern.str("");
	pattern << "^" << dupt << "$";
	ret = std::regex_match("08:5:6", match, std::regex(pattern.str()));
	if (ret)
	{
		for (auto& elem : match)
			std::cout << elem << std::endl;
	}

	pattern.str("");
	pattern << "^" << dtpt << "\\s+?" << dupt << "$";
	ret = std::regex_match("2008-5-6 08:5:6", match, std::regex(pattern.str()));
	if (ret)
	{
		for (auto& elem : match)
			std::cout << elem << std::endl;
	}
}


void CompareMatchAndSearch()
{
	//const std::string input = "Some people, when confronted with a problem, think \"I know, I'll use regular expressions.\"";
	const std::string input = "Some people, when confronted with a problem, think \"I know, I'll use regular expressions.\"";
	//const std::string pattern = "(le)";
	const std::string pattern = "[a-zA-Z]*le[a-zA-Z]*";
	std::smatch sm;

	std::cout << "match result:" << std::endl;
	if (std::regex_match(input, sm, std::regex(pattern)))
	{
		for (auto& elem : sm)
			std::cout << elem << std::endl;
	}
	
	std::cout << "search result:" << std::endl;
	if (std::regex_search(input, sm, std::regex(pattern)))
	{
		for (auto& elem : sm)
		{
			std::cout << elem << std::endl;
			auto s = elem.length();
		}
	}
}

void RegexSearchAll()
{
	const std::string input = "Some people, when confronted with a problem, think \"I know, I'll use regular expressions.\"";
	const std::string pattern = "[a-zA-Z]*(l)(e)[a-zA-Z]*";
	std::smatch sm;

	auto begIt = input.begin();
	auto endIt = input.end();
	while (std::regex_search(begIt, endIt, sm, std::regex(pattern)))
	{
		for (auto& elem : sm)
		{
			std::cout << elem << std::endl;
		}

		auto& subMatch = sm[0];
		/*std::string sbtr(subMatch.first, subMatch.second);
		std::cout << sbtr << std::endl;*/

		std::cout << "-----------------------------" << std::endl;
		begIt = subMatch.second;
	}
}

bool RegexUtil::Search(const string &srcStr, const string &pattern, vector<string> &results)
{
	std::smatch sm;
	if (!std::regex_search(srcStr, sm, std::regex(pattern)))
	{
		return false;
	}

	for (auto &elem : sm)
	{
		results.emplace_back(std::string(elem.first, elem.second));
	}
	return true;
}

bool RegexUtil::Match(const string &srcStr, const string &pattern)
{
	std::smatch sm;
	return std::regex_match(srcStr, sm, std::regex(pattern));
}

bool RegexUtil::Exist(const string &srcStr, const string &pattern)
{
	return std::regex_search(srcStr, std::regex(pattern));
}

void TestRegexUtil()
{
	const std::string input = "Some people, when confronted with a problem, think \"I know, I'll use regular expressions.\"";
	const std::string pattern = "[a-zA-Z]*(l)(e)[a-zA-Z]*";

	auto rslt = RegexUtil::Match(input, pattern);
	if (rslt)
	{
		std::cout << "match success" << std::endl;
	}
	else
	{
		std::cout << "match failed" << std::endl;
	}

	rslt = RegexUtil::Exist(input, pattern);
	if (rslt)
	{
		std::cout << "pattern is exist" << std::endl;
	}
	else
	{
		std::cout << "pattern is not exist" << std::endl;
	}

	vector<string> results;
	rslt = RegexUtil::Search(input, pattern, results);
	if (rslt)
	{
		cout << "search results: " << endl;
		for (const auto& strRslt : results)
		{
			cout << "\t" << strRslt << endl;
		}
	}
	else
	{
		std::cout << "pattern is not exist" << std::endl;
	}
}