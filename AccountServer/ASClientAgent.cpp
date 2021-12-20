#include "stdafx.h"
#include "ASClientAgent.h"

#define AS_CLIENT_LISTEN_IP "127.0.0.1"
#define AS_CLIENT_LISTEN_PORT 11451


ASClientAgent::ASClientAgent()
{

}

ASClientAgent::~ASClientAgent()
{

}

bool ASClientAgent::Init()
{
    bool bResult  = false;
    bool bRetCode = false;

    bRetCode = Bind(AS_CLIENT_LISTEN_IP, AS_CLIENT_LISTEN_PORT);
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_BOOL_END
}

void ASClientAgent::UnInit()
{

}

void ASClientAgent::Active()
{
    ProcessNetwork();
}

void ASClientAgent::ProcessPackage(int nConnIndex, byte* pbyData, size_t uDataLen)
{

}

void ASClientAgent::NewConnection(int nConnIndex, const char szIP[], int nPort)
{

}

void ASClientAgent::DisConnection(int nConnIndex)
{

}