#include "TimeUtil.h"
#include <time.h>
//#include "../../AgentInterface.h"

#ifdef SPTC11
#	include <chrono>
#else
#	ifdef __GNUC__
#	include <sys/time.h>
#	else
#		ifdef WIN32
#  		include <windows.h>
		static int gettimeofday(struct timeval *tp, void *tzp)
		{
			SYSTEMTIME wst;
			GetLocalTime(&wst);

			struct tm nowtm;
			nowtm.tm_year = wst.wYear - 1900;
			nowtm.tm_mon = wst.wMonth - 1;
			nowtm.tm_mday = wst.wDay;
			nowtm.tm_hour = wst.wHour;
			nowtm.tm_min = wst.wMinute;
			nowtm.tm_sec = wst.wSecond;
			nowtm.tm_isdst = -1;

			time_t clock = mktime(&nowtm);
			tp->tv_sec = clock;
			tp->tv_usec = wst.wMilliseconds * 1000;
			return (0);
		}
#		endif
#	endif
#endif

#ifdef WIN32
#   pragma warning(disable:4996)
#endif


long long GetCurrentMillisecond()
{
#ifdef SPTC11
	auto nowpt = chrono::system_clock::now();
    auto nowdt = nowpt.time_since_epoch();
    auto nowms = chrono::duration_cast<chrono::milliseconds>(nowdt);
    return nowms.count();
#else
	struct timeval tv;
    gettimeofday(&tv, NULL);
    long long nowms = (long long)tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return nowms;
#endif
}

bool GetDatatimeString(char* buf, size_t size, const char* format /*= NULL*/)
{
	if (!buf || !size)
	{
		return false;
	}

#ifdef SPTC11
	auto nowpt = std::chrono::system_clock::now();
	auto nowtt = std::chrono::system_clock::to_time_t(nowpt);
#else
	time_t nowtt = time(NULL);
#endif

	if (!format)
	{
		format = "%Y-%m-%d %H:%M:%S";
	}

	try
	{
        strftime(buf, size, format, localtime(&nowtt));
	}
#ifdef SPTC11
    catch (std::exception& e)
	{
		//WriteLog(e.what(), 0, 0);
		return false;
	}
#else
    catch (...)
    {
        std::cout << "format time string failed!" << std::endl;
        return false;
    }
#endif // SPTC11

	return true;
}



