#include "CustomThread.h"

#ifdef SPTC11

#include <chrono>

CustomThread::CustomThread(PFThreadCallFunc pfn, void *arg) : mBaseThread(pfn, arg), mValide(true)
{
}

#else

#include <unistd.h>

CustomThread::CustomThread(PFThreadCallFunc pfn, void *arg) : mBaseThread(0), mValide(false), mJoinable(true)
{
    int rslt = pthread_create(&mBaseThread, NULL, pfn, arg);
    mValide = (rslt != 0);
    if (rslt != 0)
    {
        cout << "create thread failed, result: " << rslt << endl;
    }
}

#endif

CustomThread::~CustomThread()
{
    mValide = false;
#ifndef SPTC11
    mJoinable = false;
#endif
}

thrd_t CustomThread::CurrentThreadID()
{
#ifdef SPTC11
    return this_thread::get_id();
#else
    return pthread_self();
#endif
}

size_t CustomThread::CovertThrdT(const thrd_t &thrd)
{
#ifdef SPTC11
    return hash<thread::id>{}(thrd);
#else
    return static_cast<size_t>(thrd);
#endif
}

void CustomThread::SleepForSecs(size_t secs)
{
#ifdef SPTC11
    this_thread::sleep_for(std::chrono::seconds(secs));
#else
    sleep(secs);
#endif
}

void CustomThread::SleepForMillSecs(size_t millsecs)
{
#ifdef SPTC11
    this_thread::sleep_for(std::chrono::microseconds(millsecs));
#else
    usleep(millsecs);
#endif
}

thrd_t CustomThread::GetThreadID()
{
#ifdef SPTC11
    return mBaseThread.get_id();
#else
    return mBaseThread;
#endif
}

bool CustomThread::IsSameThread(const thrd_t& thrdID)
{
#ifdef SPTC11
    return GetThreadID() == thrdID;
#else
    return pthread_equal(mBaseThread, thrdID) == 0;
#endif
}

bool CustomThread::Joinable()
{
#ifdef SPTC11
    return mBaseThread.joinable();
#else
    return mJoinable;
#endif
}

void CustomThread::Join()
{
#ifdef SPTC11
    mBaseThread.join();
#else
    if (mJoinable)
    {
        pthread_join(mBaseThread, NULL);
        mJoinable = false;
    }
#endif
}

void CustomThread::Detach()
{
#ifdef SPTC11
    mBaseThread.detach();
#else
    if (mJoinable)
    {
        pthread_detach(mBaseThread);
        mJoinable = false;
    }
#endif
}
