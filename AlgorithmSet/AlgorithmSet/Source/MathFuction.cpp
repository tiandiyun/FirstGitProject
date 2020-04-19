#include "MathFuction.h"
#include <iostream>
#include <iomanip>
#include <list>
#include <ios>
#include <algorithm>
#include <assert.h>
#include "TestNumerics.h"
#include "CustomRandom.h"

/*
* ���� m * x + n * y = t, m��n��tΪ����
* --> y = (t - mx) / n
* --> ���Ҫ���� y >= 0, ��Ҫ x <= t / m
*/



void DrawFunction()
{
	int m, n, t;
	std::cin >> m >> n >> t;

	int lcm = Lcm(m, n);
	t = t / lcm * lcm;
	std::cout << m << " * x + " << n << " * y = " << t << std::endl;

	int Fx = t / m;
	int Fy = (t - m * Fx) / n;
	std::cout << "Fx: " << Fx << ", Fy: " << Fy << std::endl;
}


bool SplitScore(int totalScore, int splitBase, int splitCount, int minMultiple, std::list<int>& splitedScore)
{
    // ������ܶ��Ƿ�Ϊ��ֻ�������������ͬʱ��ֵĺ�����Ҳ����Ϊ��ֻ�������������
    if (totalScore % splitBase != 0)
    {
        return false;
    }

    int remain = totalScore / splitBase;    // �Ƚ�����ܶ���Բ�ֻ������������Ϻ��ٸ��Գ��Բ�ֻ���.
    minMultiple = (std::max)(minMultiple, static_cast<int>((minMultiple - 1) / splitBase + 1));

    // ������ܶ��ڱ�֤ÿ����ְ�������С����ǰ���£��Ƿ񹻷֡�
    if (remain < minMultiple * splitCount)
    {
        return false;
    }
    remain -= minMultiple * splitCount;   // �Ƚ�ʣ��ĺ���ܶ��ȥ��ְ���Сֵ�ĺͣ��������Ϻ��ٸ��Լ�����Сֵ���ֵ��

    // ������ɣ�divCount - 1����ʣ�����ܶΧ�ڵĵ�
    std::list<int> pointList;
    for (int i = 0; i < splitCount - 1; ++i)
    {
        int pt = RangeRndI(0, remain);
        pointList.emplace_back(pt);
    }
    pointList.sort();

    // ��ʣ�����ܶ�����з֣��зֵ�ͬʱ��ÿ����ֵİ�Ҫ����֮ǰ��������Сֵ��Ȼ���ٳ��Բ�ֻ���
    splitedScore.clear();
    int prePt = 0;
    for (auto it = pointList.begin(); it != pointList.end(); ++it)
    {
        splitedScore.emplace_back((*it - prePt + minMultiple) * splitBase);
        prePt = *it;
    }
    splitedScore.emplace_back((remain - prePt + minMultiple) * splitBase);

    return true;
}

int GetMinScore(std::list<int>::iterator beg, std::list<int>::iterator end)
{
    int tmp = -1;
    int i = 0;
    for (auto it = beg; it != end; ++it)
    {
        int score = *it;
        if (i++ == 0 || score < tmp)
        {
            tmp = score;
        }
    }
    return tmp;
}

int GetMinScore(std::list<int>& scoreList)
{
    return GetMinScore(scoreList.begin(), scoreList.end());
}

/*
* ������b
* ��ӪA������Na����������Nca���е�����Cca����Ҫ����Noa���е�����Noa
* ��ӪB������Nb����������Ncb���е�����Ccb����Ҫ����Nob���е�����Nob
*/
void SimulatDDZBalance()
{
	int base = 1000, ta = 30000, tb = 50000;
	int Na, Nca, Noa, Cca, Coa;
	int Nb, Ncb, Nob, Ccb, Cob;

	/*int lcm = Lcm(Na, Nb);
	base *= lcm;*/

    std::list<int> scoreListA, scoreListB;

    int flag = 0;
    do
    {
        std::cout << "Enter amount of A and B(neither larger than 9 nor smaller than 1)" << std::endl;
        std::cin >> Na >> Nb;
        std::cout << "Amount of A: " << Na << std::endl;
        std::cout << "Amount of B: " << Nb << std::endl;
        assert(Na >= 1 && Na < 10 && Nb >= 1 && Nb < 10);

        Nca = RangeRndI(1, Na - 1);
        Noa = Na - Nca;
        std::cout << "A: Amount of charges and other is: " << Nca << ", " << Noa << std::endl;

        Ncb = RangeRndI(1, Nb - 1);
        Nob = Nb - Ncb;
        std::cout << "B: Amount of charges and other is: " << Ncb << ", " << Nob << std::endl;

        scoreListA.clear();
        SplitScore(ta, 1, Na, 1, scoreListA);
        std::cout << "A: Take scores: ";
        for (auto& score : scoreListA)
        {
            std::cout << score << ", ";
        }
        std::cout << std::endl;

        scoreListB.clear();
        SplitScore(tb, 1, Nb, 1, scoreListB);
        std::cout << "B: Take scores: ";
        for (auto& score : scoreListB)
        {
            std::cout << score << ", ";
        }
        std::cout << std::endl;

        /////////////////////////////////////////////
        GetMinScore(scoreListA);

        std::cout << "\nto be continue" << std::endl;
    } while (std::cin >> flag && flag != 0);
}