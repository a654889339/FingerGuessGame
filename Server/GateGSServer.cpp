#include "stdafx.h"
#include "GateGSServer.h"
#include "ServerWorld.h"

GateGSServer::GateGSServer()
{

    memset(m_ProcessProtocolFuns, 0, sizeof(m_ProcessProtocolFuns));
    memset(m_nProtocolSize, 0, sizeof(m_nProtocolSize));

    REGISTER_EXTERNAL_FUNC(c2s_ping_request, &GateGSServer::OnC2SPingRequest, sizeof(C2S_PING_REQUEST));
    REGISTER_EXTERNAL_FUNC(c2s_quit_notify, &GateGSServer::OnC2SQuitNotify, sizeof(C2S_QUIT_NOTIFY));
    REGISTER_EXTERNAL_FUNC(c2s_login_request, &GateGSServer::OnC2SLoginRequest, sizeof(C2S_LOGIN_REQUEST))
}
GateGSServer::~GateGSServer()
{

}

bool GateGSServer::Init(const char szIP[], int nPort)
{
    bool bResult  = false;
    bool bRetCode = false;

    bRetCode = g_pServer->m_GamePlay.m_SystemManager.AddSystem((SystemObj*)&m_ConnectionSystem);
    JYLOG_PROCESS_ERROR(bRetCode);

    REGISTER_SYSTEM_COMPONENT(m_ConnectionSystem, m_ConnectionCList);

    bRetCode = Bind(szIP, nPort);
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_BOOL_END
}

void GateGSServer::UnInit()
{

}

void GateGSServer::Active()
{
    ProcessNetwork();
}

bool GateGSServer::DoS2CPingRespond(int nConnIndex)
{
    bool bResult = false;
    bool bRetCode = false;
    S2C_PING_RESPOND Respond;

    Respond.wProtocolID = s2c_ping_respond;

    bRetCode = Send(nConnIndex, &Respond, sizeof(Respond));
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_BOOL_END
}

bool GateGSServer::DoS2CLoginRespond(int nConnIndex, int nRetCode)
{
    bool bResult = false;
    bool bRetCode = false;
    S2C_LOGIN_RESPOND Respond;

    Respond.wProtocolID = s2c_login_respond;
    Respond.nRetCode = nRetCode;

    bRetCode = Send(nConnIndex, &Respond, sizeof(Respond));
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_BOOL_END
}

//////////////////////////////////////////////////////////////////////////

void GateGSServer::OnC2SPingRequest(int nConnIndex, BYTE* pbyData, size_t uDataLen)
{
    DoS2CPingRespond(nConnIndex);
}

void GateGSServer::OnC2SQuitNotify(int nConnIndex, BYTE* pbyData, size_t uDataLen)
{
    Shutdown(nConnIndex);
}

void GateGSServer::OnC2SLoginRequest(int nConnIndex, BYTE* pbyData, size_t uDataLen)
{
    int                    nResult = pec_invalid;
    bool                   bRetCode = false;
    C2S_LOGIN_REQUEST* pRequest = (C2S_LOGIN_REQUEST*)pbyData;

    //bRetCode = g_pServer->m_PlayerManager.IsOnline(pRequest->szName);
    //JY_PROCESS_ERROR_RET_CODE(!bRetCode, pec_login_already_exist);

    //bRetCode = bRetCode = g_pServer->m_PlayerManager.AddPlayer(nConnIndex, pRequest->szName);
    //JY_PROCESS_ERROR(bRetCode);

    //bRetCode = g_pServer->m_PlayerManager.SetState(nConnIndex, egame_state_idle);
    //JY_PROCESS_ERROR(bRetCode);

    nResult = pec_login_succeed;
//Exit0:
    DoS2CLoginRespond(nConnIndex, nResult);
    if (nResult != pec_login_succeed)
    {
        Shutdown(nConnIndex);
    }
    return;
}

void GateGSServer::ProcessPackage(int nConnIndex, BYTE* pbyData, size_t uDataLen)
{
    PROTOCOL_HEADER* pHeader = (PROTOCOL_HEADER*)pbyData;
    PROCESS_PROTOCOL_FUNC Func = NULL;

    JYLOG_PROCESS_ERROR(pbyData);
    JYLOG_PROCESS_ERROR(uDataLen >= sizeof(PROTOCOL_HEADER));
    JYLOG_PROCESS_ERROR(c2s_begin < pHeader->wProtocolID && pHeader->wProtocolID < c2s_end);

    if (m_nProtocolSize[pHeader->wProtocolID] != UNDEFINED_PROTOCOL_SIZE)
    {
        JYLOG_PROCESS_ERROR(uDataLen == m_nProtocolSize[pHeader->wProtocolID]);
    }

    Func = m_ProcessProtocolFuns[pHeader->wProtocolID];
    JYLOG_PROCESS_ERROR(Func);

    (this->*Func)(nConnIndex, pbyData, uDataLen);

    JY_STD_VOID_END;
}

void GateGSServer::NewConnection(int nConnIndex, int* pnIP, int nPort)
{
    printf("[ServerConnection] New Client Connect: %s:%d, ConnIndex:%d\n", inet_ntoa(*(in_addr*)pnIP), nPort, nConnIndex);
}

void GateGSServer::DisConnection(int nConnIndex)
{
    printf("[ServerConnection] Client Connect Lost: ConnIndex:%d\n", nConnIndex);
    //g_pServer->m_PlayerManager.RemovePlayer(nConnIndex);
}
