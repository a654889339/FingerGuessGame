#include "stdafx.h"
#include "ASClientAgent.h"


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

    bRetCode = Bind(CLIENT_ACCOUNT_SERVER_LISTEN_IP, CLIENT_ACCOUNT_SERVER_LISTEN_PORT);
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_BOOL_END
}

void ASClientAgent::UnInit()
{
    Quit();
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