#include "CustomThread.h"

#ifdef SPTC11

#include <chrono>

CustomThread::CustomThread(PFThreadCallFunc pfn, void *arg) : mBaseThread(pfn, arg), mValide(true)
{
}

#else

#include <unistd.h>

CustomThread::CustomThread(PFThreadCallFunc pfn, void *arg) : mBaseThread(0), mValide(false), mJoinable(false)
{
    int rslt = pthread_create(&mBaseThread, NULL, pfn, arg);
    mValide = (rslt == 0);
    if (mValide)
    {
        pthread_attr_t attr;
        pthread_attr_init(&attr);

        int state;
        int ret = pthread_attr_getdetachstate(&attr, &state);
        if (0 == ret)
        {
            mJoinable = ((PTHREAD_CREATE_JOINABLE & state) == PTHREAD_CREATE_JOINABLE);
        }
        else
        {
            cout << "pthread_attr_getdetachstate: " << ret;
        }
    }
    else
    {
        cout << "create thread failed, result: " << rslt << endl;
    }
}

#endif

CustomThread::~CustomThread()
{
    mValide = false;
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

bool CustomThread::IsSameThread(const thrd_t &thrdID)
{
#ifdef SPTC11
    return GetThreadID() == thrdID;
#else
    return pthread_equal(mBaseThread, thrdID) == 0;
#endif
}

bool CustomThread::Joinable()
{
    if (!mValide)
    {
        return false;
    }
    
#ifdef SPTC11
    return mBaseThread.joinable();
#else
    return mJoinable;
#endif
}

void CustomThread::Join()
{
    if (!mValide)
    {
        return;
    }

#ifdef SPTC11
    mBaseThread.join();
#else
    pthread_join(mBaseThread, NULL);
    mJoinable = false;
#endif
}

void CustomThread::Detach()
{
    if (!mValide)
    {
        return;
    }
    
#ifdef SPTC11
    mBaseThread.detach();
#else
    pthread_detach(mBaseThread);
    mJoinable = false;
#endif
}
