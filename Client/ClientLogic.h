#ifndef _CLIENT_LOGIN_H_
#define _CLIENT_LOGIN_H_

#include "ClientControl.h"
#include "ClientGateAgent.h"
#include "Player.h"
#include "ClientBase.h"
#include "ClientStateManager.h"

class ClientLogic
{
public:
    ClientLogic();
    virtual ~ClientLogic();

    bool Init();
    void UnInit();

    void Run();
    void Quit();

private:
    bool CheckQuitComplete();
    bool LoadConfig();

public:
    char m_szGateIP[_NAME_LEN];
    int  m_nGatePort;
    char m_szPlayerName[_NAME_LEN];

    time_t             m_nTimeNow;
    Player             m_Player;
    ClientStateManager m_ClientStateManager;
    ClientControl      m_Control;
    ClientGateAgent   m_Connection;

private:
    bool m_bQuitFlag;
};

extern ClientLogic* g_pClient;
#endif