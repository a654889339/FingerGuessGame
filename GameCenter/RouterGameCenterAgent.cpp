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

    bRetCode = m_Agent.Init(ermt_account);
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

void RouterGameCenterAgent::ProcessNetwork()
{
    bool                  bRetCode    = false;
    BYTE*                 pbyData     = NULL;
    size_t                uDataLen    = 0;
    RouterModuleType      eType       = ermt_begin;
    uint16_t              nProtocolID = 0;
    PROCESS_PROTOCOL_FUNC Func;

    while (true)
    {
        pbyData = m_byRecvBuffer;

        bRetCode = m_Agent.Recv(sizeof(m_byRecvBuffer), pbyData, &uDataLen, &eType, &nProtocolID);
        JY_PROCESS_ERROR(bRetCode);
        JYLOG_PROCESS_ERROR(nProtocolID < m_ProcessProtocolFuns[eType].size());

        if (m_ProcessProtocolSize[eType][nProtocolID] != UNDEFINED_PROTOCOL_SIZE)
        {
            JYLOG_PROCESS_ERROR(m_ProcessProtocolSize[eType][nProtocolID] == uDataLen);
        }

        Func = m_ProcessProtocolFuns[eType][nProtocolID];
        JYLOG_PROCESS_ERROR(Func);

        (this->*Func)(pbyData, uDataLen);
    }

    JY_STD_VOID_END
}
