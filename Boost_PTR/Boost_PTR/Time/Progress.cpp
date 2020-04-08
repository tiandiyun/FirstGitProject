#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <thread>
#include <boost/progress.hpp>

void TestProgressTime()
{
	std::stringstream ss;
	{
		boost::progress_timer pt(ss);
		int i = 10240 * 10240;
		while (i-- >= 0);
	}
	std::cout << ss.str() << std::endl;
}

void TestProgressDisplay()
{
	std::vector<std::string> v(100);
	boost::progress_display pd(v.size());

	std::chrono::milliseconds dur(300);
	std::ofstream of("./text.txt");
	for (auto & x : v)
	{
		of << x << std::endl;
		std::this_thread::sleep_for(dur);
		++pd;
	}
}