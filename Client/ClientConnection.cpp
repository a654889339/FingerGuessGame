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
    REGISTER_EXTERNAL_FUNC(s2c_join_game_respond, &ClientConnection::OnS2CJoinGameRespond, sizeof(S2C_JOIN_GAME_RESPOND));
    REGISTER_EXTERNAL_FUNC(s2c_player_join_game_respond, &ClientConnection::OnS2CPlayerJoinGameRespond, sizeof(S2C_PLAYER_JOIN_GAME_RESPOND));
    REGISTER_EXTERNAL_FUNC(s2c_game_result_notify, &ClientConnection::OnS2CGameResultNotify, sizeof(S2C_GAME_RESULT_NOTIFY));
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
    DoC2SQuitNotify();
    Sleep(100);
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

bool ClientConnection::DoC2SQuitNotify()
{
    bool bResult = false;
    bool bRetCode = false;
    C2S_QUIT_NOTIFY Notify;

    Notify.wProtocolID = c2s_quit_notify;

    bRetCode = Send((byte*)&Notify, sizeof(Notify));
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

bool ClientConnection::DoJoinGameRequest(const char szName[])
{
    bool bResult = false;
    bool bRetCode = false;
    C2S_JOIN_GAME_REQUEST Request;

    Request.wProtocolID = c2s_join_game_request;
    strncpy(Request.szName, szName, sizeof(Request.szName));
    Request.szName[sizeof(Request.szName) - 1] = '\0';

    bRetCode = Send((byte*)&Request, sizeof(Request));
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_BOOL_END
}

bool ClientConnection::DoC2SPlayGameNotify(GameOperateCode eCode)
{
    bool bResult = false;
    bool bRetCode = false;
    C2S_PLAY_GAME_NOTIFY Notify;

    Notify.wProtocolID = c2s_play_game_notify;
    Notify.nGameOperateCode = (int)eCode;

    bRetCode = Send((byte*)&Notify, sizeof(Notify));
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
        JYLOG_PROCESS_ERROR(false);
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
        printf("昵称:%s, 分数:%d, 状态:%s\n", pPlayerInfo[i].szName, pPlayerInfo[i].nScore, szGameState[(GameState)pPlayerInfo[i].nState]);
    }

    JY_STD_VOID_END
}

void ClientConnection::OnS2CCreateGameRespond(BYTE* pbyData, size_t uSize)
{
    S2C_CREATE_GAME_RESPOND *pRespond = (S2C_CREATE_GAME_RESPOND*) pbyData;

    JYLOG_PROCESS_ERROR(pRespond);

    switch (pRespond->nRetCode)
    {
    case pec_create_round_succeed:
        g_pClient->SetState(egame_state_waiting);
        break;

    case pec_create_round_already:
        puts("已在战局中");
        break;

    default:
        JYLOG_PROCESS_ERROR(false);
    }

    JY_STD_VOID_END;
}

void ClientConnection::OnS2CJoinGameRespond(BYTE* pbyData, size_t uSize)
{
    S2C_JOIN_GAME_RESPOND* pRespond = (S2C_JOIN_GAME_RESPOND*)pbyData;

    JYLOG_PROCESS_ERROR(pRespond);

    switch (pRespond->nRetCode)
    {
    case pec_join_game_succeed:
        g_pClient->SetState(egame_state_playing);
        break;

    case pec_join_game_player_not_found:
        puts("对方不在线");
        g_pClient->SetState(egame_state_idle);
        break;

    case pec_join_game_not_found:
        puts("对方未开启战局");
        g_pClient->SetState(egame_state_idle);
        break;

    case pec_join_game_already_begun:
        puts("对方已在战局中");
        g_pClient->SetState(egame_state_idle);
        break;

    default:
        JYLOG_PROCESS_ERROR(false);
    }

    JY_STD_VOID_END;
}

void ClientConnection::OnS2CPlayerJoinGameRespond(BYTE* pbyData, size_t uSize)
{
    S2C_PLAYER_JOIN_GAME_RESPOND* pRespond = (S2C_PLAYER_JOIN_GAME_RESPOND*)pbyData;

    JYLOG_PROCESS_ERROR(pRespond);

    printf("玩家:%s 加入战局。\n", pRespond->szName);
    g_pClient->SetState(egame_state_playing);

    JY_STD_VOID_END;
}

void ClientConnection::OnS2CGameResultNotify(BYTE* pbyData, size_t uSize)
{
    S2C_GAME_RESULT_NOTIFY* pNotify = (S2C_GAME_RESULT_NOTIFY*)pbyData;

    JYLOG_PROCESS_ERROR(pNotify);

    switch ((GameResultCode)pNotify->nGameResult)
    {
    case erc_win:
        printf("获胜，得分:%d。\n", pNotify->nScore);
        break;
    case erc_lose:
        printf("战败，得分:%d。\n", pNotify->nScore);
        break;
    case erc_draw:
        printf("平局，得分:%d。\n", pNotify->nScore);
        break;
    case erc_invalid:
        printf("本局失效，得分:%d。\n", pNotify->nScore);
        break;
    }

    g_pClient->SetState(egame_state_idle);

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