#include "stdafx.h"
#include "ClientASAgent.h"
#include "ClientTip.h"
#include "ClientLogic.h"

ClientASAgent::ClientASAgent()
{
    m_bLoginFlag = false;

    memset(m_ProcessProtocolFuns, 0, sizeof(m_ProcessProtocolFuns));
    memset(m_nProtocolSize, 0, sizeof(m_nProtocolSize));

    REGISTER_EXTERNAL_FUNC(eas2c_login_respond, &ClientASAgent::OnAS2CLoginRespond, sizeof(AS2C_LOGIN_RESPOND));
}

ClientASAgent::~ClientASAgent()
{

}

bool ClientASAgent::Init()
{
    bool bResult  = false;
    bool bRetCode = false;

    bRetCode = Connect(CLIENT_ACCOUNT_SERVER_LISTEN_IP, CLIENT_ACCOUNT_SERVER_LISTEN_PORT);
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_BOOL_END
}

void ClientASAgent::UnInit()
{
    Quit();
}

void ClientASAgent::Active()
{
    ProcessNetwork();
}

void ClientASAgent::Login(char* pszAccountName, char* pszPassword)
{
    bool bRetCode = false;

    JYLOG_PROCESS_ERROR(pszAccountName);
    JYLOG_PROCESS_ERROR(pszPassword);

    bRetCode = DoC2ASLoginRequest(pszAccountName, pszPassword);
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_VOID_END
}

bool ClientASAgent::DoC2ASLoginRequest(char* pszAccountName, char* pszPassword)
{
    bool                bResult  = false;
    bool                bRetCode = false;
    C2AS_LOGIN_REQUEST* pRequest = (C2AS_LOGIN_REQUEST*)GetSendBuffer(sizeof(C2AS_LOGIN_REQUEST));

    JYLOG_PROCESS_ERROR(pRequest);
    JYLOG_PROCESS_ERROR(pszAccountName);
    JYLOG_PROCESS_ERROR(pszPassword);

    pRequest->wProtocolID           = ec2as_login_request;
    pRequest->nAccountServerVersion = ACCOUNT_SERVER_VERSION;

    strncpy(pRequest->szAccountName, pszAccountName, sizeof(pRequest->szAccountName));
    pRequest->szAccountName[sizeof(pRequest->szAccountName) - 1] = '\0';

    strncpy(pRequest->szPassword, pszPassword, sizeof(pRequest->szPassword));
    pRequest->szPassword[sizeof(pRequest->szPassword) - 1] = '\0';

    bRetCode = Send(pRequest, sizeof(C2AS_LOGIN_REQUEST));
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_BOOL_END
}

//////////////////////////////////////////////////////////////////////////
void ClientASAgent::ProcessPackage(BYTE* pbyData, size_t uDataLen)
{
    PROTOCOL_HEADER*      pHeader = (PROTOCOL_HEADER*)pbyData;
    PROCESS_PROTOCOL_FUNC Func    = NULL;

    JYLOG_PROCESS_ERROR(pbyData);
    JYLOG_PROCESS_ERROR(uDataLen >= sizeof(PROTOCOL_HEADER));
    JYLOG_PROCESS_ERROR(eas2c_begin < pHeader->wProtocolID&& pHeader->wProtocolID < eas2c_end);

    if (m_nProtocolSize[pHeader->wProtocolID] != UNDEFINED_PROTOCOL_SIZE)
    {
        JYLOG_PROCESS_ERROR(uDataLen == m_nProtocolSize[pHeader->wProtocolID]);
    }

    Func = m_ProcessProtocolFuns[pHeader->wProtocolID];
    JYLOG_PROCESS_ERROR(Func);

    (this->*Func)(pbyData, uDataLen);

    JY_STD_VOID_END;
}

void ClientASAgent::ConnectionLost()
{
    printf("[ASAgent] Connection lost.\n");
}

void ClientASAgent::OnAS2CLoginRespond(BYTE* pbyData, size_t uDataLen)
{
    AS2C_LOGIN_RESPOND* pRespond = (AS2C_LOGIN_RESPOND*)pbyData;

    JYLOG_PROCESS_ERROR(pRespond->nResultCode > eas2c_begin && pRespond->nResultCode < eas2c_end);

    printf("[ASAgent] Login Result: %s\n", szLoginResult[pRespond->nResultCode]);

    if (pRespond->nResultCode == elrc_success)
    {
        strncpy(g_pClient->m_szGateIP, inet_ntoa(*(IN_ADDR*)&pRespond->uGateIP), sizeof(g_pClient->m_szGateIP));
        g_pClient->m_nGatePort = pRespond->nGatePort;

        g_pClient->m_ClientStateManager.Set(ecst_wait_to_connect_gate);
    }
    else
        g_pClient->m_ClientStateManager.Set(ecst_init_client);

    JY_STD_VOID_END
}