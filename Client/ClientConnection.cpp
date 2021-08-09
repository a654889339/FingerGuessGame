#include "stdafx.h"
#include "ClientConnection.h"
#include "ClientWorld.h"

#define REGISTER_EXTERNAL_FUNC(ProtocolID, FuncName, ProtocolSize)  \
{m_ProcessProtocolFuns[ProtocolID] = FuncName;                  \
    m_nProtocolSize[ProtocolID] = ProtocolSize;}

ClientConnection::ClientConnection()
{
    m_nNextPingTime = 0;

    memset(m_ProcessProtocolFuns, 0, sizeof(m_ProcessProtocolFuns));
    memset(m_nProtocolSize, 0, sizeof(m_nProtocolSize));

    REGISTER_EXTERNAL_FUNC(s2c_ping_respond, &ClientConnection::OnS2CPingRespond, sizeof(S2C_PING_RESPOND));
    REGISTER_EXTERNAL_FUNC(s2c_login_respond, &ClientConnection::OnS2CLoginRespond, sizeof(S2C_LOGIN_RESPOND));
    REGISTER_EXTERNAL_FUNC(s2c_apply_all_player_respond, &ClientConnection::OnS2CApplyAllPlayerRespond, UNDEFINED_PROTOCOL_SIZE);
    REGISTER_EXTERNAL_FUNC(s2c_create_game_respond, &ClientConnection::OnS2CCreateGameRespond, sizeof(S2C_CREATE_GAME_RESPOND));
}

ClientConnection::~ClientConnection()
{

}

bool ClientConnection::Init(const char szIP[], int nPort)
{
    bool bResult = false;
    bool bRetCode = false;

    JYLOG_PROCESS_ERROR(szIP);

    bRetCode = Connect(szIP, nPort);
    JYLOG_PROCESS_ERROR(bRetCode);

    g_pClient->SetState(egame_state_login);

    bRetCode = DoC2SLoginRequest();
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_BOOL_END
}

void ClientConnection::UnInit()
{

}

void ClientConnection::Active()
{
    ProcessNetwork();

    if (IsEnable() && m_nNextPingTime < g_pClient->m_nTimeNow)
    {
        m_nNextPingTime = g_pClient->m_nTimeNow + PING_TIME_INTERVAL;
        DoC2SPingRequest();
    }
}

void ClientConnection::DisConnect()
{
    Quit();
}

bool ClientConnection::DoC2SPingRequest()
{
    bool bResult = false;
    bool bRetCode = false;
    C2S_PING_REQUEST Request;

    Request.wProtocolID = c2s_ping_request;

    bRetCode = Send((byte*)&Request, sizeof(Request));
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

    bRetCode = Send((byte*)&Request, sizeof(Request));
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_BOOL_END
}

bool ClientConnection::DoC2SApplyAllPlayerRequest()
{
    bool bResult = false;
    bool bRetCode = false;
    C2S_APPLY_ALL_PLAYER_REQUEST Request;

    Request.wProtocolID = c2s_apply_all_player_request;

    bRetCode = Send((byte*)&Request, sizeof(Request));
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_BOOL_END
}

bool ClientConnection::DoCreateGameRequest()
{
    bool bResult = false;
    bool bRetCode = false;
    C2S_CREATE_GAME_REQUEST Request;

    Request.wProtocolID = c2s_create_game_request;

    bRetCode = Send((byte*)&Request, sizeof(Request));
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
            g_pClient->m_szIP, g_pClient->m_nPort
        );
        g_pClient->SetState(egame_state_idle);
        break;

    case pec_login_already_exist:
        printf("[ClientConnection] Name:%s already login.\n", g_pClient->m_szPlayerName);

        g_pClient->Quit();
        break;

    default:
        g_pClient->Quit();
    }

    JY_STD_VOID_END
}

void ClientConnection::OnS2CApplyAllPlayerRespond(BYTE* pbyData, size_t uSize)
{
    S2C_APPLY_ALL_PLAYER_RESPOND* pRespond = (S2C_APPLY_ALL_PLAYER_RESPOND*)pbyData;
    SHOW_PLAYER_INFO* pPlayerInfo = NULL;

    JYLOG_PROCESS_ERROR(pRespond);

    printf("在线人数: %d\n", pRespond->nCount);

    pPlayerInfo = (SHOW_PLAYER_INFO*)pRespond->byData;
    JYLOG_PROCESS_ERROR(pPlayerInfo);

    for(int i = 0; i < pRespond->nCount; i++)
    {
        printf("%s %s\n", pPlayerInfo[i].szName, szGameState[(GameState)pPlayerInfo[i].nState]);
    }

    JY_STD_VOID_END
}

void ClientConnection::OnS2CCreateGameRespond(BYTE* pbyData, size_t uSize)
{
    S2C_CREATE_GAME_RESPOND *pRespond = (S2C_CREATE_GAME_RESPOND*) pbyData;
    JYLOG_PROCESS_ERROR(pRespond);
    if(pRespond->nRetCode == 1)
    {
        g_pClient->SetState(egame_state_waiting);
    }
    else
    {
        printf("%s", "创建失败");
    }
    JY_STD_VOID_END;
}

void ClientConnection::ProcessPackage(byte* pbyData, size_t uDataLen)
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
    g_pClient->SetState(egame_state_begin);
    g_pClient->Quit();
}