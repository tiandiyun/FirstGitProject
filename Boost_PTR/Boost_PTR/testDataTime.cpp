#include <time.h>
#include "testDataTime.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include "boost/date_time/gregorian/greg_date.hpp"

void CompareDate()
{
    boost::gregorian::date today = boost::gregorian::day_clock::local_day();

    tm tmpTm;
    time_t tmpTime = time(NULL) + 100;
    localtime_s(&tmpTm, &tmpTime);
    boost::gregorian::date weakenDay = boost::gregorian::date_from_tm(tmpTm);

    if (today > weakenDay)
    {
        std::cout << "today > weakenDay" << std::endl;
    } 
    else if (today < weakenDay)
    {
        std::cout << "today < weakenDay" << std::endl;
    }
    else
    {
        std::cout << "today < weakenDay" << std::endl;
    }

    boost::posix_time::ptime nowTime = boost::posix_time::second_clock::local_time();
    std::string strISOTime = boost::posix_time::to_iso_string(nowTime);
    std::string strSimpleTime = boost::posix_time::to_simple_string(nowTime);
    std::cout << strISOTime << std::endl;
    std::cout << strSimpleTime << std::endl;
}