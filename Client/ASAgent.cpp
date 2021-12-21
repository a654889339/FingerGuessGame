#include "stdafx.h"
#include "ASAgent.h"

ASAgent::ASAgent()
{
    m_bLoginFlag = false;
}

ASAgent::~ASAgent()
{

}

bool ASAgent::Init()
{
    bool bResult = false;

    JY_STD_BOOL_END
}

void ASAgent::UnInit()
{

}

void ASAgent::Active()
{
    ProcessNetwork();
}

void ASAgent::SetLogin(bool bLoginFlag)
{
    bool bRetCode = false;

    JY_PROCESS_ERROR(m_bLoginFlag != bLoginFlag);

    if (bLoginFlag)
    {
        bRetCode = Connect(CLIENT_ACCOUNT_SERVER_LISTEN_IP, CLIENT_ACCOUNT_SERVER_LISTEN_PORT);
        JYLOG_PROCESS_ERROR(bRetCode);
    }
    else
    {
        Quit();
    }

    m_bLoginFlag = bLoginFlag;

    JY_STD_VOID_END
}

//////////////////////////////////////////////////////////////////////////
void ASAgent::ProcessPackage(byte* pbyData, size_t uDataLen)
{

}

void ASAgent::ConnectionLost()
{

}