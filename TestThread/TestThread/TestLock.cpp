#include "stdafx.h"
#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <queue>
#include <random>
#include "TestLock.h"


std::mutex              g_lockprint;
std::mutex              g_lockqueue;
std::condition_variable g_queuecheck;
std::queue<int>         g_codes;
bool                    g_done;
bool                    g_notified;



//////////////////////////////////////////////////////////////////////////

void UniqLock()
{
    printf("[%d] try lock.\n", std::this_thread::get_id());
    std::unique_lock<std::mutex> locker(g_lockprint);
    printf("[%d] locked it, will sleep.\n", std::this_thread::get_id());

    std::this_thread::sleep_for(std::chrono::seconds(3));
    printf("[%d] wake up, will release lock.\n", std::this_thread::get_id());
}

void TestUniqLock()
{
    std::vector<std::thread> threads;
    for (int i = 0; i < 3; ++i)
    {
        threads.push_back(std::thread(UniqLock));
    }

    for (auto& t : threads)
        t.join();
}


//////////////////////////////////////////////////////////////////////////

void workerfunc(int id, std::mt19937& generator)
{
    // print a starting message
    {
        std::unique_lock<std::mutex> locker(g_lockprint);
        std::cout << "[worker " << id << "]\trunning..." << std::endl;
    }

    // simulate work
    std::this_thread::sleep_for(std::chrono::seconds(1 + generator() % 5));

    // simulate error
    int errorcode = id * 100 + 1;
    {
        std::unique_lock<std::mutex> locker(g_lockprint);
        std::cout << "[worker " << id << "]\tan error occurred: " << errorcode << std::endl;
    }

    // notify error to be logged
    {
        std::unique_lock<std::mutex> locker(g_lockqueue);
        g_codes.push(errorcode);
        g_notified = true;
        g_queuecheck.notify_one();
    }
}

void loggerfunc()
{
    // print a starting message
    {
        std::unique_lock<std::mutex> locker(g_lockprint);
        std::cout << "[logger]\trunning..." << std::endl;
    }

    // loop until end is signaled
    while (!g_done)
    {
        std::unique_lock<std::mutex> locker(g_lockqueue);

        while (!g_notified) // used to avoid spurious wakeups 
        {
            g_queuecheck.wait(locker);
        }

        // if there are error codes in the queue process them
        while (!g_codes.empty())
        {
            std::unique_lock<std::mutex> locker(g_lockprint);
            std::cout << "[logger]\tprocessing error:  " << g_codes.front() << std::endl;
            g_codes.pop();
        }

        g_notified = false;
    }
}

void TestConditionVarible()
{
    // initialize a random generator
    std::mt19937 generator((unsigned int)std::chrono::system_clock::now().time_since_epoch().count());

    // start the logger
    std::thread loggerthread(loggerfunc);

    // start the working threads
    std::vector<std::thread> threads;
    for (int i = 0; i < 5; ++i)
    {
        threads.push_back(std::thread(workerfunc, i + 1, std::ref(generator)));
    }

    // work for the workers to finish
    for (auto& t : threads)
        t.join();

    // notify the logger to finish and wait for it
    g_done = true;
    loggerthread.join();
}



//////////////////////////////////////////////////////////////////////////

void ConditionUniqLock(int id)
{
    printf("[%d] try lock...\n", id);
    std::unique_lock<std::mutex> locker(g_lockprint);

    if (id % 2 == 0)
    {
        printf("[%d] locked it, wait.\n\n", id);
        g_queuecheck.wait(locker);
        printf("[%d] wake up, sleep.\n\n", id);
        
        std::this_thread::sleep_for(std::chrono::seconds(3));
        printf("[%d] sleep over, release lock.\n", id);
    } 
    else
    {
        printf("[%d] locked it, notify.\n", id);
        g_queuecheck.notify_one();
        printf("[%d] notify one, release lock.\n", id);
    }
}

void TestConditionUniqLock()
{
    std::vector<std::thread> threads;
    for (int i = 0; i < 4; ++i)
    {
        threads.push_back(std::thread(ConditionUniqLock, i));
    }

    for (auto& t : threads)
        t.join();
}