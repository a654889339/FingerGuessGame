#include "stdafx.h"
#include "ClientWorld.h"

void PLAYER_STATE_IDLE::Enter(GameState eState, Player* pPlayer)
{
    puts(szStateContent[m_eState]);
}

void PLAYER_STATE_WAITING::Enter(GameState eState, Player* pPlayer)
{
    puts(szStateContent[m_eState]);
}

void PLAYER_STATE_WAITING::Leave(GameState eState, Player* pPlayer)
{
    puts(eState == egame_state_playing ? "ƥ��ɹ�" : "�ص�����");
}

void PLAYER_STATE_PLAYING::Enter(GameState eState, Player* pPlayer)
{
    puts(szStateContent[m_eState]);
}

void PLAYER_STATE_PLAYING::Leave(GameState eState, Player* pPlayer)
{
    if (eState == egame_state_idle)
        puts("�ص�����");
}

ClientWorld::ClientWorld()
{
    m_nPort = 0;
    m_bQuitFlag = false;
    m_nTimeNow = 0;

    m_PlayerState[egame_state_idle] = &m_PlayerStateIdle;
    m_PlayerState[egame_state_waiting] = &m_PlayerStateWaiting;
    m_PlayerState[egame_state_playing] = &m_PlayerStatePlaying;

    memset(m_szIP, 0, sizeof(m_szIP));
}

ClientWorld::~ClientWorld()
{

}

bool ClientWorld::Init()
{
    bool bResult = false;
    bool bRetCode = false;
    bool bControlInitFlag = false;
    bool bConnInitFlag = false;

    m_nTimeNow = time(NULL);

    bRetCode = LoadConfig();
    JYLOG_PROCESS_ERROR(bRetCode);

    bRetCode = m_Control.Init();
    JYLOG_PROCESS_ERROR(bRetCode);
    bControlInitFlag = true;

    bRetCode = m_Connection.Init(m_szIP, m_nPort);
    JYLOG_PROCESS_ERROR(bRetCode);
    bConnInitFlag = true;

    bResult = true;
Exit0:
    if (!bResult)
    {
        if (bConnInitFlag)
        {
            bConnInitFlag = false;
            m_Connection.UnInit();
        }

        if (bControlInitFlag)
        {
            bControlInitFlag = false;
            m_Control.UnInit();
        }
    }
    return bResult;
}

void ClientWorld::UnInit()
{
    m_Connection.UnInit();
    m_Control.UnInit();
}

void ClientWorld::Run()
{
    while (true)
    {
        m_nTimeNow = time(NULL);

        JY_PROCESS_ERROR(!CheckQuitComplete());

        m_Control.Active();
        m_Connection.Active();

        Sleep(10);
    }

    JY_STD_VOID_END
}

void ClientWorld::Quit()
{
    m_bQuitFlag = true;
    m_Connection.DisConnect();
}

void ClientWorld::SetState(GameState eState)
{
    SetPlayerState(&m_Player, eState);
}

// Private
bool ClientWorld::CheckQuitComplete()
{
    bool bResult = false;

    JY_PROCESS_ERROR(m_bQuitFlag);
    JY_PROCESS_ERROR(!m_Connection.IsEnable());

    JY_STD_BOOL_END;
}

bool ClientWorld::LoadConfig()
{
    bool bResult = false;
    bool bRetCode = false;

    strcpy(m_szIP, "127.0.0.1");
    m_nPort = 5566;

    printf("[ClientWorld] Input your name:\n");
    while (true)
    {
        scanf("%s", m_szPlayerName);
        m_szPlayerName[sizeof(m_szPlayerName) - 1] = '\0';
        bRetCode = CheckNickName(m_szPlayerName);
        if (bRetCode)
        {
            break;
        }
        else
            puts("���зǷ��ַ�������������.");
    }

    JY_STD_BOOL_END
}