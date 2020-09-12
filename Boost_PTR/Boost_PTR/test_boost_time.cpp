#include "test_boost_time.h"
#include <iostream>
#include <boost/date_time/time_clock.hpp>
#include <boost/date_time/c_local_time_adjustor.hpp>
#include <boost/chrono/duration.hpp>
#include <chrono>

void PtimeFromString()
{
    //boost::posix_time::ptime pt = boost::posix_time::time_from_string("2002-01-20 23:59:59.000");
    boost::posix_time::ptime pt = boost::posix_time::time_from_string("2002-01-31 25");
    boost::posix_time::ptime pt2 = boost::posix_time::time_from_string("2003-01-31 25");

    boost::posix_time::time_duration td = boost::posix_time::duration_from_string("18");
    
    //auto tdms = boost::chrono::duration_cast<boost::chrono::milliseconds>(pt2 - pt);

    std::cout << "pt: " << pt << std::endl;
    std::cout << "td: " << td << std::endl;

    boost::posix_time::ptime now_pt = boost::posix_time::second_clock::local_time();
    std::cout << "now_pt: " << now_pt << std::endl;

    std::cout << td.total_seconds() << ", " << td.total_milliseconds() << std::endl;
    
    std::chrono::time_point<std::chrono::system_clock> stdPt = std::chrono::system_clock::now();
    std::time_t std_t = std::chrono::system_clock::to_time_t(stdPt);

    std::chrono::seconds::rep std_dur = std::chrono::duration_cast<std::chrono::seconds>(stdPt.time_since_epoch()).count();

    boost::gregorian::date d = boost::gregorian::from_string("2020-01-31");
    std::tm dtm = boost::gregorian::to_tm(d);

    boost::posix_time::time_duration tds = boost::posix_time::duration_from_string("08:10:35");
    std::tm tdtm = boost::posix_time::to_tm(tds); 
    auto secs = tds.total_seconds(); 

    std::tm tempTm = {};
    tempTm.tm_hour = 8;
    tempTm.tm_min = 24;
    tempTm.tm_sec = 35;

    std::time_t tempTt = std::mktime(&tempTm);
}


void DateCompare()
{
    boost::posix_time::ptime pt1 = boost::posix_time::from_time_t(1583096400);
    boost::posix_time::ptime pt2 = boost::posix_time::from_time_t(1583132400);
    boost::posix_time::ptime localPt1 = boost::date_time::c_local_adjustor<boost::posix_time::ptime>::utc_to_local(pt1);
    boost::posix_time::ptime localPt2 = boost::date_time::c_local_adjustor<boost::posix_time::ptime>::utc_to_local(pt2);
    boost::gregorian::date dt1 = localPt1.date();
    boost::gregorian::date dt2 = localPt2.date();

    std::cout << "dt1: " << boost::gregorian::to_simple_string(dt1).c_str() << std::endl;
    std::cout << "dt2: " << boost::gregorian::to_simple_string(dt2).c_str() << std::endl;
    if (dt1 > dt2)
    {
        std::cout << "dt1 > dt2" << std::endl;
    }
    else if (dt1 < dt2)
    {
        std::cout << "dt1 < dt2" << std::endl;
    }
    else if (dt1 == dt2)
    {
        std::cout << "dt1 == dt2" << std::endl;
    }
    else
    {
        std::cout << "erro" << std::endl;
    }

    /*boost::posix_time::ptime temppt1(dt1);
    std::cout << "pt1: " << boost::posix_time::to_simple_string(pt1) << std::endl;
    std::cout << "temppt1: " << boost::posix_time::to_simple_string(temppt1) << std::endl;*/
}

#define TIMETYPE  1

void TestDateTime()
{
    /* Simple program that uses the gregorian calendar to progress by exactly
    * one month, irregardless of how many days are in that month.
    *
    * This method can be used as an alternative to iterators
    */

    std::time_t begintt = 1585638000;
    boost::posix_time::ptime nowpt = boost::posix_time::second_clock::universal_time();
    auto localNowPt = boost::date_time::c_local_adjustor<boost::posix_time::ptime>::utc_to_local(nowpt);
    std::cout << "now time: " << boost::posix_time::to_simple_string(localNowPt).c_str() << std::endl;

#if (TIMETYPE == 0) 
    {
        // 按周
        std::time_t weekstt = 86400 * 7;      
        boost::posix_time::ptime begpt = boost::posix_time::from_time_t(begintt);

        boost::posix_time::time_duration offsettt(8, 0, 0);
        begpt += offsettt;

        boost::posix_time::time_duration deltatd = nowpt - begpt;
        int weekDiff = deltatd.total_seconds() / weekstt;
        begpt += boost::posix_time::seconds(weekstt * weekDiff);
        if (begpt < nowpt)
        {
            begpt += boost::posix_time::seconds(weekstt);
        }

        auto localBeginPt = boost::date_time::c_local_adjustor<boost::posix_time::ptime>::utc_to_local(begpt);
        std::cout << "begin time: " << boost::posix_time::to_simple_string(localBeginPt).c_str() << std::endl;
    }
#elif (TIMETYPE == 1) 
    {
        // 按月
        boost::gregorian::date nowDt = nowpt.date();

        boost::posix_time::ptime begpt = boost::posix_time::from_time_t(begintt);
        boost::posix_time::ptime localBegPt = boost::date_time::c_local_adjustor<boost::posix_time::ptime>::utc_to_local(begpt);
        boost::gregorian::date begDt = localBegPt.date();
        std::cout << "begin day: " << begDt.day() << std::endl;

        boost::gregorian::months oneMonth(1);
        while (begDt < nowDt)
        {
            begDt += oneMonth;
        }
    }

#endif
}
