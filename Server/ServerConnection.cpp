#include "stdafx.h"
#include "ServerConnection.h"
#include "ServerWorld.h"

#define REGISTER_EXTERNAL_FUNC(ProtocolID, FuncName, ProtocolSize)  \
{m_ProcessProtocolFuns[ProtocolID] = FuncName;                  \
    m_nProtocolSize[ProtocolID] = ProtocolSize;}

ServerConnection::ServerConnection()
{

    memset(m_ProcessProtocolFuns, 0, sizeof(m_ProcessProtocolFuns));
    memset(m_nProtocolSize, 0, sizeof(m_nProtocolSize));

    REGISTER_EXTERNAL_FUNC(c2s_ping_request, &ServerConnection::OnC2SPingRequest, sizeof(C2S_PING_REQUEST));
    REGISTER_EXTERNAL_FUNC(c2s_quit_notify, &ServerConnection::OnC2SQuitNotify, sizeof(C2S_QUIT_NOTIFY));
    REGISTER_EXTERNAL_FUNC(c2s_login_request, &ServerConnection::OnC2SLoginRequest, sizeof(C2S_LOGIN_REQUEST));
    REGISTER_EXTERNAL_FUNC(c2s_apply_all_player_request, &ServerConnection::OnC2SApplyAllPlayerRequest, sizeof(C2S_APPLY_ALL_PLAYER_REQUEST));
    REGISTER_EXTERNAL_FUNC(c2s_create_game_request, &ServerConnection::OnC2SCreateGameRequest, sizeof(C2S_CREATE_GAME_REQUEST));
    REGISTER_EXTERNAL_FUNC(c2s_join_game_request, &ServerConnection::OnC2SJoinGameRequest, sizeof(C2S_JOIN_GAME_REQUEST));
    REGISTER_EXTERNAL_FUNC(c2s_play_game_notify, &ServerConnection::OnC2SPlayGameNotify, sizeof(C2S_PLAY_GAME_NOTIFY));
}
ServerConnection::~ServerConnection()
{

}

bool ServerConnection::Init(const char szIP[], int nPort)
{
    bool bResult = false;
    bool bRetCode = false;

    bRetCode = Bind(szIP, nPort);
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_BOOL_END
}

void ServerConnection::UnInit()
{

}

void ServerConnection::Active()
{
    ProcessNetwork();
}

bool ServerConnection::DoS2CPingRespond(int nConnIndex)
{
    bool bResult = false;
    bool bRetCode = false;
    S2C_PING_RESPOND Respond;

    Respond.wProtocolID = s2c_ping_respond;

    bRetCode = Send(nConnIndex, &Respond, sizeof(Respond));
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_BOOL_END
}

bool ServerConnection::DoS2CLoginRespond(int nConnIndex, int nRetCode)
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

struct KGetAllPlayerInfoFunc
{
    int nCount;
    SHOW_PLAYER_INFO* pInfo;
    bool operator ()(Player* pPlayer);
};

bool KGetAllPlayerInfoFunc::operator ()(Player* pPlayer)
{
    bool bResult = false;

    JYLOG_PROCESS_ERROR(pInfo);
    JYLOG_PROCESS_ERROR(pPlayer);

    strncpy(pInfo->szName, pPlayer->m_szName, sizeof(pInfo->szName));
    pInfo->nScore = pPlayer->m_nScore;
    pInfo->nState = (int)pPlayer->m_eState;
    pInfo++;
    nCount++;

    JY_STD_BOOL_END
}

bool ServerConnection::DoS2CApplyAllPlayerRespond(int nConnIndex)
{
    bool bResult = false;
    bool bRetCode = false;
    S2C_APPLY_ALL_PLAYER_RESPOND* pRespond = (S2C_APPLY_ALL_PLAYER_RESPOND*)m_szTempBuffer;
    KGetAllPlayerInfoFunc Func;

    pRespond->wProtocolID = s2c_apply_all_player_respond;

    Func.nCount = 0;
    Func.pInfo = (SHOW_PLAYER_INFO*)pRespond->byData;

    bRetCode = g_pServer->m_PlayerManager.m_PlayerMap.traversal(Func);
    JYLOG_PROCESS_ERROR(bRetCode);

    pRespond->nCount = Func.nCount;

    bRetCode = Send(nConnIndex, pRespond, sizeof(S2C_APPLY_ALL_PLAYER_RESPOND) + pRespond->nCount * sizeof(SHOW_PLAYER_INFO));
    JY_PROCESS_ERROR(bRetCode);

    JY_STD_BOOL_END
}

bool ServerConnection::DoS2CCreateGameRespond(int nConnIndex, int nRetCode)
{
    bool bResult = false;
    bool bRetCode = false;
    S2C_CREATE_GAME_RESPOND Respond;

    Respond.wProtocolID = s2c_create_game_respond;
    Respond.nRetCode = nRetCode;

    bRetCode = Send(nConnIndex, &Respond, sizeof(Respond));
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_BOOL_END
}

bool ServerConnection::DoS2CJoinGameRespond(int nConnIndex, int nRetCode)
{
    bool bResult = false;
    bool bRetCode = false;
    S2C_JOIN_GAME_RESPOND Respond;

    Respond.wProtocolID = s2c_join_game_respond;
    Respond.nRetCode = nRetCode;

    bRetCode = Send(nConnIndex, &Respond, sizeof(Respond));
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_BOOL_END
}

bool ServerConnection::DoS2CPlayerJoinGameRespond(int nConnIndex, const char szName[])
{
    bool bResult = false;
    bool bRetCode = false;
    S2C_PLAYER_JOIN_GAME_RESPOND Respond;

    Respond.wProtocolID = s2c_player_join_game_respond;
    strncpy(Respond.szName, szName, sizeof(Respond.szName));
    Respond.szName[sizeof(Respond.szName) - 1] = '\0';

    bRetCode = Send(nConnIndex, &Respond, sizeof(Respond));
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_BOOL_END
}

bool ServerConnection::DoS2CGameResultNotify(int nConnIndex, int nScore, GameResultCode eGameResult)
{
    bool bResult = false;
    bool bRetCode = false;
    S2C_GAME_RESULT_NOTIFY Notify;

    Notify.wProtocolID = s2c_game_result_notify;
    Notify.nScore = nScore;
    Notify.nGameResult = (int)eGameResult;

    bRetCode = Send(nConnIndex, &Notify, sizeof(Notify));
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_BOOL_END
}
//////////////////////////////////////////////////////////////////////////

void ServerConnection::OnC2SPingRequest(int nConnIndex, byte* pbyData, size_t uDataLen)
{
    DoS2CPingRespond(nConnIndex);
}

void ServerConnection::OnC2SQuitNotify(int nConnIndex, byte* pbyData, size_t uDataLen)
{
    Shutdown(nConnIndex);
}

void ServerConnection::OnC2SLoginRequest(int nConnIndex, byte* pbyData, size_t uDataLen)
{
    int                    nResult = pec_invalid;
    bool                   bRetCode = false;
    C2S_LOGIN_REQUEST* pRequest = (C2S_LOGIN_REQUEST*)pbyData;

    bRetCode = g_pServer->m_PlayerManager.IsOnline(pRequest->szName);
    JY_PROCESS_ERROR_RET_CODE(!bRetCode, pec_login_already_exist);

    bRetCode = bRetCode = g_pServer->m_PlayerManager.AddPlayer(nConnIndex, pRequest->szName);
    JY_PROCESS_ERROR(bRetCode);

    bRetCode = g_pServer->m_PlayerManager.SetState(nConnIndex, egame_state_idle);
    JY_PROCESS_ERROR(bRetCode);

    nResult = pec_login_succeed;
Exit0:
    DoS2CLoginRespond(nConnIndex, nResult);
    if (nResult != pec_login_succeed)
    {
        Shutdown(nConnIndex);
    }
    return;
}

void ServerConnection::OnC2SApplyAllPlayerRequest(int nConnIndex, byte* pbyData, size_t uDataLen)
{
    DoS2CApplyAllPlayerRespond(nConnIndex);
}

void ServerConnection::OnC2SCreateGameRequest(int nConnIndex, byte* pbyData, size_t uDataLen)
{
    int nResult = pec_create_round_already;
    bool bRetCode = false;
    Player* pPlayer = NULL;

    pPlayer = g_pServer->m_PlayerManager.GetPlayer(nConnIndex);
    JY_PROCESS_ERROR(pPlayer);

    JY_PROCESS_ERROR(pPlayer->m_eState == egame_state_idle);
    bRetCode = g_pServer->m_PlayerManager.SetState(nConnIndex, egame_state_waiting);
    JYLOG_PROCESS_ERROR(bRetCode);

    nResult = pec_create_round_succeed;
Exit0:
    DoS2CCreateGameRespond(nConnIndex, nResult);
}

void ServerConnection::OnC2SJoinGameRequest(int nConnIndex, byte* pbyData, size_t uDataLen)
{
    int nResult = pec_join_game_not_found;
    bool bRetCode = false;
    C2S_JOIN_GAME_REQUEST* pRequest = (C2S_JOIN_GAME_REQUEST*)pbyData;
    Player* pHost = NULL;

    pHost = g_pServer->m_PlayerManager.GetPlayer(pRequest->szName);
    JY_PROCESS_ERROR_RET_CODE(pHost, pec_join_game_player_not_found);
    JY_PROCESS_ERROR_RET_CODE(pHost->m_nConnIndex != nConnIndex, pec_join_game_self);
    JY_PROCESS_ERROR(pHost->m_eState == egame_state_waiting);

    bRetCode = g_pServer->m_PlayerManager.JoinGame(nConnIndex, pHost);
    JYLOG_PROCESS_ERROR(bRetCode);

    nResult = pec_join_game_succeed;
Exit0:
    DoS2CJoinGameRespond(nConnIndex, nResult);
}

void ServerConnection::OnC2SPlayGameNotify(int nConnIndex, byte* pbyData, size_t uDataLen)
{
    bool bRetCode = false;
    C2S_PLAY_GAME_NOTIFY* pNotify = (C2S_PLAY_GAME_NOTIFY*)pbyData;
    Player* pPlayer = NULL;

    pPlayer = g_pServer->m_PlayerManager.GetPlayer(nConnIndex);
    JYLOG_PROCESS_ERROR(pPlayer);

    JY_PROCESS_ERROR(pPlayer->m_eState == egame_state_playing);

    pPlayer->m_eGameOperateCode = (GameOperateCode)pNotify->nGameOperateCode;
    pPlayer->m_bOperate = true;

    g_pServer->m_PlayerManager.TryEndGame(nConnIndex);

    JY_STD_VOID_END
}

void ServerConnection::ProcessPackage(int nConnIndex, byte* pbyData, size_t uDataLen)
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

void ServerConnection::NewConnection(int nConnIndex, const char szIP[], int nPort)
{
    printf("[ServerConnection] New Client Connect: %s:%d, ConnIndex:%d\n", szIP, nPort, nConnIndex);
}

void ServerConnection::DisConnection(int nConnIndex)
{
    printf("[ServerConnection] Client Connect Lost: ConnIndex:%d\n", nConnIndex);
    g_pServer->m_PlayerManager.RemovePlayer(nConnIndex);
}
