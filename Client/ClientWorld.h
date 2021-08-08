#ifndef _CLIENT_WORLD_H_
#define _CLIENT_WORLD_H_

#include "ClientControl.h"
#include "ClientConnection.h"

enum ClientGameState
{
    egame_state_login,
    egame_state_idle,
    egame_state_waiting,
    egame_state_playing,
};

class ClientWorld
{
public:
    ClientWorld();
    virtual ~ClientWorld();

    bool Init();
    void UnInit();

    void Run();
    void Quit();

private:
    bool CheckQuitComplete();
    bool LoadConfig();

public:
    char m_szIP[_NAME_LEN];
    int  m_nPort;
    time_t m_nTimeNow;
    char m_szPlayerName[_NAME_LEN];
    ClientGameState m_eGameState;

public:
    ClientControl    m_Control;
    ClientConnection m_Connection;

private:
    bool m_bQuitFlag;
};

extern ClientWorld* g_pClient;
#endif