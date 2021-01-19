#ifndef TIME_UTIL_H_
#define TIME_UTIL_H_

#include "DataDefine.h"
#include <iostream>

using namespace std;

long long GetCurrentMillisecond();

bool GetDatatimeString(char* buf, size_t size, const char* format = NULL);

#endif
