#pragma once

#include <ctime>

class timer
{
public:
    timer() { _start_time = std::clock(); } // postcondition: elapsed()==0

    //         timer( const timer& src );      // post: elapsed()==src.elapsed()

    //        ~timer(){}

    //  timer& operator=( const timer& src );  // post: elapsed()==src.elapsed()

    void   restart() { _start_time = std::clock(); } // post: elapsed()==0

    double elapsed() const                  // return elapsed time in seconds
    {
        return  double(std::clock() - _start_time) / CLOCKS_PER_SEC;
    }

    std::clock_t elapsed_millisecond() const                  // return elapsed time in seconds
    {
        return  std::clock() - _start_time;
    }

    double elapsed_max() const   // return estimated maximum value for elapsed()
        // Portability warning: elapsed_max() may return too high a value on systems
        // where std::clock_t overflows or resets at surprising values.
    {
        return (double((std::numeric_limits<std::clock_t>::max)())
            - double(_start_time)) / double(CLOCKS_PER_SEC);
    }

    double elapsed_min() const            // return minimum value for elapsed()
    {
        return double(1) / double(CLOCKS_PER_SEC);
    }

private:
    std::clock_t _start_time;
}; // timer