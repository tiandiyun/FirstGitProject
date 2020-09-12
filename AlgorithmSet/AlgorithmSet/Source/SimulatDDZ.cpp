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
* 函数 m * x + n * y = t, m、n和t为常数
* --> y = (t - mx) / n
* --> 如果要满足 y >= 0, 需要 x <= t / m
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


static bool SplitScore(int totalScore, int splitBase, int splitCount, int minMultiple, std::list<int>& splitedScore)
{
    // 检查红包总额是否为拆分基数的整数倍，同时拆分的红包金额也必须为拆分基数的整数倍。
    if (totalScore % splitBase != 0)
    {
        return false;
    }

    int remain = totalScore / splitBase;    // 先将红包总额除以拆分基数，待拆分完毕后，再各自乘以拆分基数.
    minMultiple = (std::max)(minMultiple, static_cast<int>((minMultiple - 1) / splitBase + 1));

    // 检查红包总额在保证每个拆分包满足最小金额的前提下，是否够分。
    if (remain < minMultiple * splitCount)
    {
        return false;
    }
    remain -= minMultiple * splitCount;   // 先将剩余的红包总额，减去拆分包最小值的和，待拆分完毕后，再各自加上最小值红包值。

    // 随机生成（divCount - 1）个剩余红包总额范围内的点
    std::list<int> pointList;
    for (int i = 0; i < splitCount - 1; ++i)
    {
        int pt = RangeRndI(0, remain);
        pointList.emplace_back(pt);
    }
    pointList.sort();

    // 对剩余红包总额进行切分，切分的同时，每个拆分的包要加上之前减掉的最小值，然后再乘以拆分基数
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

static int GetMinScore(std::list<int>::iterator beg, std::list<int>::iterator end)
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

static int GetMinScore(std::list<int>& scoreList)
{
    return GetMinScore(scoreList.begin(), scoreList.end());
}

static void GetEachMinScore(std::list<int>& scoreList, int chargersCount, int& chargersLowerLimit, int& othersLowerLimit, int& lowerLimit)
{
    auto beg = scoreList.begin();
    auto end = std::next(beg, chargersCount);
    chargersLowerLimit = GetMinScore(beg, end);

    beg = end;
    end = scoreList.end();
    othersLowerLimit = GetMinScore(beg, end);

    lowerLimit = std::min(chargersLowerLimit, othersLowerLimit);
}

static int AlignLcm(int digit, int align)
{
    return align == 0 ? digit : digit / align * align;
}

void CalcEachBalance(int balanceTotal, int chargersCount, int othersCount, int chargersScoreMin, int& chargersBalanceBase, int& othersBalacneBase)
{
    int blanceBase = balanceTotal / (chargersCount + othersCount);
    int chargersBalaceTotal = std::min(chargersScoreMin * chargersCount, balanceTotal);

    int lcm = Lcm(chargersCount, othersCount);
    int base = blanceBase * chargersCount;
    int supply = AlignLcm(chargersBalaceTotal - base, lcm);
    chargersBalaceTotal = base + supply;

    chargersBalanceBase = chargersBalaceTotal / chargersCount;
    othersBalacneBase = othersCount == 0 ? 0 : (balanceTotal - chargersBalaceTotal) / othersCount;

    assert(balanceTotal == chargersBalanceBase * chargersCount + othersBalacneBase * othersCount);
}

void ShowCarriedSocres(std::list<int>& scoreList, const char* name)
{
    if (name)
    {
        std::cout << "(" << name << ")";
    }

    size_t i = 0;
    std::cout << " Scores carried: ";
    for (auto& score : scoreList)
    {
        std::cout << score;
        if (++i < scoreList.size())
        {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
}

/*
* 基础分b
* 阵营A，人数Na，责任人数Nca，承担费用Cca，次要人数Noa，承担费用Noa
* 阵营B，人数Nb，责任人数Ncb，承担费用Ccb，次要人数Nob，承担费用Nob
*/
void SimulatDDZBalance()
{
    ResetSeed();

	int base = 1000, ta = 30000, tb = 50000, total = 0;
	int Na, Nca, Noa, Cca, Coa;
	int Nb, Ncb, Nob, Ccb, Cob;

    std::list<int> scoreListA, scoreListB;

    int flag = 1;
    do
    {
        /*std::cout << "Enter amount of A and B(neither larger than 9 nor smaller than 1)" << std::endl;
        std::cin >> Na >> Nb;
        assert(Na >= 1 && Na < 10 && Nb >= 1 && Nb < 10);*/

        Na = RangeRndI(1, 10);
        Nb = RangeRndI(1, 10);

        Nca = RangeRndI(1, Na - 1);
        Noa = Na - Nca;

        Ncb = RangeRndI(1, Nb - 1);
        Nob = Nb - Ncb;

        scoreListA.clear();
        SplitScore(ta, 1, Na, 1, scoreListA);

        scoreListB.clear();
        SplitScore(tb, 1, Nb, 1, scoreListB);

        /////////////////////////////////////////////
        int minScore_a, minScore_ca, minScore_oa;
        int minScore_b, minScore_cb, minScore_ob;
        GetEachMinScore(scoreListA, Nca, minScore_ca, minScore_oa, minScore_a);
        GetEachMinScore(scoreListB, Ncb, minScore_cb, minScore_ob, minScore_b);

        int lcm = Lcm(scoreListA.size(), scoreListB.size());
        total = std::min(minScore_a * scoreListA.size(), minScore_b * scoreListB.size());
        total = std::min(total, base * lcm);
        total = AlignLcm(total, lcm);
        
        /////////////////////////////////////////////

        CalcEachBalance(total, Nca, Noa, minScore_ca, Cca, Coa);
        CalcEachBalance(total, Ncb, Nob, minScore_cb, Ccb, Cob);

        /////////////////////////////////////////////

        //ShowCarriedSocres(scoreListA, "A");
        //ShowCarriedSocres(scoreListB, "B");
        //std::cout << "(A) Amount of charges and other is: " << Nca << ", " << Noa << std::endl;
        //std::cout << "(B) Amount of charges and other is: " << Ncb << ", " << Nob << std::endl;
        ////std::cout << "A: Smallest score carried of chargers and other are:" << minScore_ca << ", " << minScore_oa << std::endl;
        ////std::cout << "B: Smallest score carried of chargers and other are:" << minScore_cb << ", " << minScore_ob << std::endl;
        ////std::cout << "Smallest score carried of A is: " << minScore_a << std::endl;
        ////std::cout << "Smallest score carried of B is: " << minScore_b << std::endl;
        //std::cout << "Base score and total balacne: " << base << ", " << total << std::endl;
        //std::cout << "(A) Balance scores of chargers and other are: " << Cca << ", " << Coa << std::endl;
        //std::cout << "(B) Balance scores of chargers and other are: " << Ccb << ", " << Cob << std::endl;

        /////////////////////////////////////////////

        /*std::cout << "\nto be continue ...\n" << std::endl;
        try
        {
            std::cin >> flag;
        }
        catch (const std::exception&)
        {
            flag = 0;
        }*/
    } while (flag != 0);
}