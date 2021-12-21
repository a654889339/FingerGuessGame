#include "stdafx.h"
#include "ASClientAgent.h"

ASClientAgent::ASClientAgent()
{
    memset(m_ProcessProtocolFuns, 0, sizeof(m_ProcessProtocolFuns));
    memset(m_nProtocolSize, 0, sizeof(m_nProtocolSize));

    REGISTER_EXTERNAL_FUNC(ec2as_login_request, &ASClientAgent::OnC2ASLoginRequest, sizeof(C2AS_LOGIN_REQUEST));
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

//////////////////////////////////////////////////////////////////////////

void ASClientAgent::ProcessPackage(int nConnIndex, BYTE* pbyData, size_t uDataLen)
{

}

void ASClientAgent::NewConnection(int nConnIndex, const char szIP[], int nPort)
{

}

void ASClientAgent::DisConnection(int nConnIndex)
{

}

void ASClientAgent::OnC2ASLoginRequest(int nConnIndex, BYTE* pbyData, size_t uDataLen)
{

}