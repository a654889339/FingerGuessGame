#include "stdafx.h"
#include "ClientConnection.h"
#include "ClientLogic.h"

#define REGISTER_EXTERNAL_FUNC(ProtocolID, FuncName, ProtocolSize)  \
{m_ProcessProtocolFuns[ProtocolID] = FuncName;                  \
    m_nProtocolSize[ProtocolID] = ProtocolSize;}

ClientConnection::ClientConnection()
{
    m_nNextPingTime = 0;
    m_nNextReconnectTime = 0;

    memset(m_ProcessProtocolFuns, 0, sizeof(m_ProcessProtocolFuns));
    memset(m_nProtocolSize, 0, sizeof(m_nProtocolSize));

    REGISTER_EXTERNAL_FUNC(s2c_ping_respond, &ClientConnection::OnS2CPingRespond, sizeof(S2C_PING_RESPOND));
    REGISTER_EXTERNAL_FUNC(s2c_login_respond, &ClientConnection::OnS2CLoginRespond, sizeof(S2C_LOGIN_RESPOND));
}

ClientConnection::~ClientConnection()
{

}

bool ClientConnection::Init()
{
    bool bResult  = false;
    bool bRetCode = false;

    JYLOG_PROCESS_ERROR(!IsEnable());

    bRetCode = Connect(g_pClient->m_szGateIP, g_pClient->m_nGatePort);
    JYLOG_PROCESS_ERROR(bRetCode);

    bRetCode = DoC2SLoginRequest();
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_BOOL_END
}

void ClientConnection::UnInit()
{
    Quit();
}

void ClientConnection::Active()
{
    ProcessNetwork();
}

void ClientConnection::DisConnect()
{
    if (IsEnable())
    {
        DoC2SQuitNotify();
        Sleep(100);
    }
    Quit();
}

bool ClientConnection::DoC2SPingRequest()
{
    bool bResult = false;
    bool bRetCode = false;
    C2S_PING_REQUEST Request;

    Request.wProtocolID = c2s_ping_request;

    bRetCode = Send((BYTE*)&Request, sizeof(Request));
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_BOOL_END
}

bool ClientConnection::DoC2SQuitNotify()
{
    bool bResult = false;
    bool bRetCode = false;
    C2S_QUIT_NOTIFY Notify;

    Notify.wProtocolID = c2s_quit_notify;

    bRetCode = Send((BYTE*)&Notify, sizeof(Notify));
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_BOOL_END
}

bool ClientConnection::DoC2SLoginRequest()
{
    bool bResult = false;
    bool bRetCode = false;
    C2S_LOGIN_REQUEST Request;

    Request.wProtocolID = c2s_login_request;
    strncpy(Request.szName, g_pClient->m_szPlayerName, sizeof(Request.szName));

    bRetCode = Send((BYTE*)&Request, sizeof(Request));
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_BOOL_END
}

// Private
void ClientConnection::OnS2CPingRespond(BYTE* pbyData, size_t uSize)
{
}

void ClientConnection::OnS2CLoginRespond(BYTE* pbyData, size_t uSize)
{
    S2C_LOGIN_RESPOND* pRespond = (S2C_LOGIN_RESPOND*)pbyData;

    JYLOG_PROCESS_ERROR(pRespond);

    switch (pRespond->nRetCode)
    {
    case pec_login_succeed:
        printf("[ClientConnection] Login Server: %s:%d Success.\n",
            g_pClient->m_szGateIP, g_pClient->m_nGatePort
        );
        g_pClient->m_ClientStateManager.Set(ecst_playing);
        break;

    case pec_login_already_exist:
        printf("[ClientConnection] Name:%s already login.\n", g_pClient->m_szPlayerName);

        g_pClient->Quit();
        break;

    default:
        JYLOG_PROCESS_ERROR(false);
    }

    JY_STD_VOID_END
}

void ClientConnection::ProcessPackage(BYTE* pbyData, size_t uDataLen)
{
    PROTOCOL_HEADER* pHeader = (PROTOCOL_HEADER*)pbyData;
    PROCESS_PROTOCOL_FUNC Func = NULL;

    JYLOG_PROCESS_ERROR(pbyData);
    JYLOG_PROCESS_ERROR(uDataLen >= sizeof(PROTOCOL_HEADER));
    JYLOG_PROCESS_ERROR(s2c_begin < pHeader->wProtocolID && pHeader->wProtocolID < s2c_end);

    if (m_nProtocolSize[pHeader->wProtocolID] != UNDEFINED_PROTOCOL_SIZE)
    {
        JYLOG_PROCESS_ERROR(uDataLen == m_nProtocolSize[pHeader->wProtocolID]);
    }

    Func = m_ProcessProtocolFuns[pHeader->wProtocolID];
    JYLOG_PROCESS_ERROR(Func);

    (this->*Func)(pbyData, uDataLen);

    JY_STD_VOID_END;
}

void ClientConnection::ConnectionLost()
{
    g_pClient->m_ClientStateManager.Set(ecst_init_client);
    g_pClient->Quit();
}