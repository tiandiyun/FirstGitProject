// TestAlgorithm.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "RedWars/RedWars.h"
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <memory>
#include <cmath>
#include "TestRegex.h"

uint32_t ExchangeTicketByLayer(uint32_t layer, uint32_t betCoin)
{
    // ��ȯ�� = min����log������ + 8, 8) - 1�� * 2 / 3��1�� * �볡��Ϸ�� / 100
    /*auto num = std::log10(layer + 8) / std::log10(8);
    auto factor = (std::min)((num - 1) * 2 / 3, 1.0);
    auto ticket_f = std::ceil(factor * betCoin / 100);*/

    auto factor = (std::log10(layer + 8) / std::log10(8) - 1) * 2 / 3;
    auto ticket_f = (std::min)(factor, 1.0) * betCoin / 100;
    auto ticket_i = static_cast<uint32_t>(std::ceil(ticket_f));
    return ticket_i;
}

int _tmain(int argc, _TCHAR* argv[])
{
    //TestRegexMatch();
	//CompareMatchAndSearch();
	//RegexSearchAll();
	TestRegexUtil();

    system("pause");
	return 0;
}

