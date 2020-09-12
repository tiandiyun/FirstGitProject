#pragma once

#include<chrono>
#include <iomanip>

void TestRep();

void TestCustomDuration();

time_t TimeFromString(const std::string &s, const char* format = nullptr);

void TestTimeGet();

long long GetCurrentMillisecond();