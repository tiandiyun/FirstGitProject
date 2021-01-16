#ifndef _CUSTOM_THREAD_H_
#define _CUSTOM_THREAD_H_

#include <iostream>

#ifdef __GNUC__
#   if __cplusplus >= 201103L
#   define SPTC11
#   endif
#elif defined(_MSC_VER)
#   if _MSC_VER >= 1700
#   define SPTC11
#   endif
#endif

using namespace std;

#ifdef SPTC11
    #include <thread>
    typedef thread::id thrd_t;
#else
    #include <pthread.h>
    typedef pthread_t thrd_t;
#endif


typedef void *(*PFThreadCallFunc)(void *);

class CustomThread
{
public:
    CustomThread(PFThreadCallFunc pfn, void *arg);

    ~CustomThread();

    static thrd_t CurrentThreadID();

    static size_t CovertThrdT(const thrd_t& thrd);

    static void SleepForSecs(size_t secs);

    static void SleepForMillSecs(size_t millsecs);

    thrd_t GetThreadID();

    bool IsSameThread(const thrd_t& thrdID);

    bool Joinable();

    void Join();

    void Detach();

private:
    CustomThread() {}

private:
#ifdef SPTC11
    thread      mBaseThread;
#else
    pthread_t   mBaseThread;
    bool        mJoinable;
#endif
    bool        mValide;
};

#endif // _CUSTOM_THREAD_H_
