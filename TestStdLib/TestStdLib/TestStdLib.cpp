// TestStdLib.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <time.h>
#include <thread>
#include <locale>

#pragma warning(disable : 4996)

using namespace std;

void TestDiv()
{
    div_t dv = div(5, 3);
    cout << "div(5, 3) -- quot: " << dv.quot << ", rem: " << dv.rem << endl;

    dv = div(4, 2);
    cout << "div(4, 2) -- quot: " << dv.quot << ", rem: " << dv.rem << endl;
}

void CoutTM(const tm* tmv, const char* title)
{
    if (!title)
        title = "tm: ";
    cout << title << endl;
    cout << setw(10) << "tm_year:" << setw(5) << tmv->tm_year << endl;
    cout << setw(10) << "tm_mon:" << setw(5) << tmv->tm_mon << endl;
    cout << setw(10) << "tm_yday:" << setw(5) << tmv->tm_yday << endl;
    cout << setw(10) << "tm_mday:" << setw(5) << tmv->tm_mday << endl;
    cout << setw(10) << "tm_wday:" << setw(5) << tmv->tm_wday << endl;
    cout << setw(10) << "tm_hour:" << setw(5) << tmv->tm_hour << endl;
    cout << setw(10) << "tm_min:" << setw(5) << tmv->tm_min << endl;
    cout << setw(10) << "tm_sec:" << setw(5) << tmv->tm_sec << endl;
    cout << setw(10) << "tm_isdst:" << setw(5) << tmv->tm_isdst << endl;
}

void TestTime()
{
    std::this_thread::sleep_for(chrono::seconds(1));

    clock_t clk = clock();
    int sec = clk / CLOCKS_PER_SEC;
    cout << "start secs " << sec << endl;

    time_t tt, tr;
    tt = time(&tr);
    cout << "tt: " << tt << ", tr: " << tr << endl;

    time_t t1 = time(nullptr);
    this_thread::sleep_for(chrono::milliseconds(1000));
    time_t t2 = time(nullptr);
    double dt = difftime(t2, t1);
    cout << t2 << " - " << t1 << " = " << dt << endl;

    const char* ct = ctime(&tt);
    cout << "ct: " << ct << endl;

    tm* gmtm = gmtime(&tt);
    CoutTM(gmtm, "gmtime returned: ");
    cout << endl;

    tm* lctm = localtime(&tt);
    CoutTM(lctm, "localtime returned: ");
    cout << endl;

    const char* asctmStr = asctime(lctm);
    cout << "asctime: " << asctmStr << endl;

    char timeStr[50];
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", lctm);
    cout << "locale time format: " << timeStr << endl;
}

void TestQSort()
{
    int srcArr[] = { 6, 8, 7, 2, 5, 3, 4, 1 };
    qsort(srcArr, sizeof(srcArr) / sizeof(srcArr[0]), sizeof(srcArr[0]), [](const void *a, const void *b)->int{
        int diff = *(reinterpret_cast<const int*>(a)) - *(reinterpret_cast<const int*>(b));
        return diff * -1;
    });

    for (int i = 0; i < sizeof(srcArr) / sizeof(srcArr[0]); ++i)
    {
        cout << srcArr[i] << ", ";
    }
}

void TestLocal()
{
    const char *lc = setlocale(LC_ALL, NULL);
    lconv *lcv = localeconv();
    lcv->decimal_point = "..";
    lcv->thousands_sep = ",,";

    float f = 1000.232f;
    printf("%5.5f", f);
}

int _tmain(int argc, _TCHAR* argv[])
{
    double a = 0;
    system("pause");
    return 0;
}

