// StdCoutAdvTest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <map>
#include <windows.h>
#include <fstream>
#include <map>
#include <algorithm>
#include <utility>

#define BIND_NAME(cmd) nameMap[cmd] = string(#cmd);

using namespace std;

map<UINT16, string> nameMap;

enum NET_COMMAND_LIST_BETWEEN_CLIENT_SERVER
{
	NET_CMD_CS_INNER_BEGIN = 3501,
	NET_CMD_CS_LOGIN_VIA_SERVER,		//��LoginServer��¼
	NET_CMD_CS_LOGIN_DIRECTLY,		//ֱ�ӵ�¼GateServer
	NET_CMD_CS_INNER_END,
};

void TestStream()
{

}

int _tmain(int argc, _TCHAR* argv[])
{
	/*cout.flags(ios::left); //�����
	cout << setw(10) << -456.98 << "The End" << endl;
	cout.flags(ios::internal); //���˶���
	cout << setw(10) << -456.98 << "The End" << endl;
	cout.flags(ios::right); //�Ҷ���
	cout << setw(10) << -456.98 << "The End" << endl;*/

	srand((unsigned)time(NULL));

	std::map<short, int> allData;
	for (int i = 0; i < 10000; ++i)
	{
		int v = (rand() % 5) + 1;
		auto it = allData.find(v);
		if (it != allData.end())
		{
			it->second += 1;
		}
		else
		{
			allData[v] = 1;
		}
	}

	/*cout << "----------------------------------------------------------" << endl;

	cout.flags(ios::left);
	for (auto fishPair : allData)
	{
	cout << setw(10) << fishPair.first;
	}
	cout << endl << endl;

	for (auto fishPair : allData)
	{
	cout << setw(10) << fishPair.second;
	}
	cout << endl;

	cout << "----------------------------------------------------------" << endl;
	*/

	/*char path[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, path);

	string patchStr{ path };
	patchStr += "\\statistic.txt";
	cout << patchStr.c_str() << endl;

	ofstream ofile;       //��������ļ�
	ofile.open(patchStr);     //��Ϊ����ļ���

	for (auto fishPair : allData)
	{
	ofile << fishPair.first << "\t";
	}
	ofile << endl;

	for (auto fishPair : allData)
	{
	ofile << fishPair.second << "\t";
	}

	ofile.close();*/

	/*
		std::map<int, char> chars;
		for (int i = 0; i < 10; ++i)
		{
		chars[i] = 'a' + i;
		}

		for_each(chars.begin(), chars.end(), [](const std::pair<int, char>& kv){ std::cout << kv.second << std::endl; });*/

	BIND_NAME(NET_CMD_CS_LOGIN_VIA_SERVER);
	BIND_NAME(NET_CMD_CS_LOGIN_DIRECTLY);

	for (auto names : nameMap)
	{
		cout << names.first << ": " << names.second.c_str() << endl;
	}

	getchar();
	return 0;
}

