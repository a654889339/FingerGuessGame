#include "stdafx.h"
#include "RouterGameCenterAgent.h"

RouterGameCenterAgent::RouterGameCenterAgent()
{
    memset(m_byRecvBuffer, 0, sizeof(m_byRecvBuffer));

    REGISTER_ROUTER_FUNC(ermt_account, eas2gc_player_login_request, &RouterGameCenterAgent::OnAS2GCPlayerLoginRequest, sizeof(AS2GC_PLAYER_LOGIN_REQUEST));
}

RouterGameCenterAgent::~RouterGameCenterAgent()
{

}

bool RouterGameCenterAgent::Init()
{
    bool bResult              = false;
    bool bRetCode             = false;
    bool bInitRouterAgentFlag = false;

    bRetCode = m_Agent.Init(ermt_gamecenter);
    JYLOG_PROCESS_ERROR(bRetCode);
    bInitRouterAgentFlag = true;

    bResult = true;
Exit0:
    if (!bResult)
    {
        if (bInitRouterAgentFlag)
        {
            m_Agent.UnInit();
            bInitRouterAgentFlag = false;
        }
    }
    return bResult;
}

void RouterGameCenterAgent::UnInit()
{
    m_Agent.UnInit();
}

void RouterGameCenterAgent::Active()
{
    ProcessNetwork();
}

bool RouterGameCenterAgent::DoGC2ASPlayerLoginRespond(uint64_t uOpenId)
{
    bool                       bResult  = false;
    bool                       bRetCode = false;
    GC2AS_PLAYER_LOGIN_RESPOND Respond;

    Respond.uOpenId = uOpenId;

    bRetCode = m_Agent.SendToModule(ermt_gamecenter, egc2as_player_login_respond, (BYTE*)&Respond, sizeof(Respond));
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_BOOL_END
}

//// Private

void RouterGameCenterAgent::OnAS2GCPlayerLoginRequest(BYTE* pbyData, size_t uSize)
{
    AS2GC_PLAYER_LOGIN_REQUEST* pRequest = (AS2GC_PLAYER_LOGIN_REQUEST*)pbyData;

    printf("[RouterGameCenterAgent] OnAS2GCPlayerLoginRequest: %llu.\n", pRequest->uOpenId);

    JY_STD_VOID_END
}

ROUTER_AGENT_IMPLEMENT(RouterGameCenterAgent)