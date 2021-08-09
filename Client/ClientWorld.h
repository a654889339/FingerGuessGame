#ifndef _CLIENT_WORLD_H_
#define _CLIENT_WORLD_H_

#include "ClientControl.h"
#include "ClientConnection.h"
#include "Player.h"

class PLAYER_STATE_IDLE : public PLAYER_STATE_TRIGGER
{
public:
    PLAYER_STATE_IDLE() {m_eState = egame_state_idle;}
    void Enter(GameState eState, Player* pPlayer);
};

class PLAYER_STATE_WAITING : public PLAYER_STATE_TRIGGER
{
public:
    PLAYER_STATE_WAITING() { m_eState = egame_state_waiting; }
    void Enter(GameState eState, Player* pPlayer);
    void Leave(GameState eState, Player* pPlayer);
};

class ClientWorld : public PLAYER_STATE_MANAGER
{
public:
    ClientWorld();
    virtual ~ClientWorld();

    bool Init();
    void UnInit();

    void Run();
    void Quit();

    void SetState(GameState eState);

private:
    bool CheckQuitComplete();
    bool LoadConfig();

public:
    char m_szIP[_NAME_LEN];
    int  m_nPort;
    time_t m_nTimeNow;
    char m_szPlayerName[_NAME_LEN];
    Player m_Player;

public:
    ClientControl    m_Control;
    ClientConnection m_Connection;

private:
    bool m_bQuitFlag;
};

extern ClientWorld* g_pClient;
#endif