#include "stdafx.h"
#include "TemplateSpecialization.h"
#include "..\DataStruct.h"

int SendMsg(SSPingRequest&)
{
    return 0;
}

void TestSpecialiatioin()
{
    PingClient::PingSendMsgHandler handler = std::bind(SendMsg, std::placeholders::_1);
    
}
