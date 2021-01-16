#pragma once

#include <iostream>
#include <vector>

using namespace std;

void TestRegexSearch();

void TestRegexMatch();

void CompareMatchAndSearch();

void RegexSearchAll();


class RegexUtil
{
public:
	static bool Search(const string &srcStr, const string &pattern, vector<string> &results);

	static bool Match(const string &srcStr, const string &pattern);

	static bool Exist(const string &srcStr, const string &pattern);
};

void TestRegexUtil();