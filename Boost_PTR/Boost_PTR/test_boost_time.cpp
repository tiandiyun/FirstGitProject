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

    std::time_t t = std::time(nullptr);


}

