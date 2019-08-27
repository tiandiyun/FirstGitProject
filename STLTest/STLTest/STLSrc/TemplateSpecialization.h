#pragma once

#include <stdint.h>
#include <functional>
#include <iostream>
#include "..\LazySingleton.h"


struct SSPingRequest
{
    int a;
};

struct SSPingResponse
{
    int b;
};


template<typename SendT, typename RecvT> class PingMsgHandler
{
public:
    using PingSendMsgHandler = std::function<int(SendT &)>;

    PingMsgHandler(PingSendMsgHandler sender) : mSender(sender) {}

    int SendMsg(SendT &msg)
    {
        if (mSender)
        {
            return mSender(msg);
        }
        return -1;
    }

    virtual void    OnPing(RecvT &msg) = 0;

protected:
    PingSendMsgHandler  mSender{ nullptr };
};



class PingBase
{
public:
    using PingTimeoutHandler = std::function<void()>;

    PingBase(uint64_t socketID)
        : mSocketID(socketID)
        , mLeftSecs(0)
    {

    }

    void Tick(float elapsedTime)
    {
        mLeftSecs -= elapsedTime;
        if (mLeftSecs <= 0)
        {
            if (mTimeoutHandler)
            {
                mTimeoutHandler();
            }
        }
    }

    bool IsTimeout()
    {
        return mLeftSecs < 0;
    }

    uint64_t GetSocketID()
    {
        return mSocketID;
    }

protected:
    PingTimeoutHandler  mTimeoutHandler{ nullptr };
    uint64_t            mSocketID{ 0 };
    float               mLeftSecs{ 0 };
};


class PingClient : public PingBase, public PingMsgHandler<SSPingRequest, SSPingResponse>
{
public:
    PingClient(uint64_t socketID, PingSendMsgHandler sender)
        : PingBase(socketID)
        , PingMsgHandler(sender)
    {
        int i = 0;
        std::cout << "hahahahah" << std::endl;
    }

    void Tick(float elapsedTime)
    {
        PingBase::Tick(elapsedTime);

        mPingLeftSecs -= elapsedTime;
        if (mPingLeftSecs <= 0)
        {
            SSPingRequest   pingMsg;
            if (SendMsg(std::move(pingMsg)) != 0)
            {
                //LOGE(__FUNCTION__ " -- Send ping request failed !!");
            }
        }
    }

    void OnPing(SSPingResponse &msg) override
    {

    }

private:
    float               mPingLeftSecs{ 0 };
};


template<typename PT,
    typename PTH = PT::PingTimeoutHandler>
class PingEntitiesManager
{
public:
    void AddPingEntity(uint64_t entityID, PTH timeoutHandler)
    {
    }
};

// class PingClientManager : public PingEntitiesManager<PingClient>, public LazySingleton<PingClientManager>{};


void TestSpecialiatioin();