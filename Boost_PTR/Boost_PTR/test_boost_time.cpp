#include "test_boost_time.h"
#include <iostream>
#include <boost/date_time/time_clock.hpp>
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


void MothAdding()
{
    /* Simple program that uses the gregorian calendar to progress by exactly
    * one month, irregardless of how many days are in that month.
    *
    * This method can be used as an alternative to iterators
    */

    auto nowtp = std::chrono::system_clock::now();
    std::time_t nowtt = std::chrono::system_clock::to_time_t(nowtp);
    std::tm nowtm = *std::localtime(&nowtt);

    std::time_t begintt = 1583078400;
    std::tm begintm = *std::localtime(&begintt);

    std::time_t weekstt = 86400 * 7;
    int weeks = (nowtt - begintt) / weekstt;
    std::time_t nexttt = begintt + weekstt * weeks;
    if (nexttt < nowtt)
    {
        nexttt += weekstt;
    }

    boost::posix_time::ptime nowpt = boost::posix_time::second_clock::local_time();
    boost::posix_time::ptime beginpt = boost::posix_time::from_time_t(begintt);
    boost::posix_time::time_duration offsettt(8, 0, 0);
    beginpt += offsettt;
    
    boost::posix_time::time_duration deltatd = nowpt - beginpt;
    boost::posix_time::time_duration weekSeconds = boost::posix_time::seconds(86400 * 7);
    auto oneWeek = boost::gregorian::weeks::unit();
}
