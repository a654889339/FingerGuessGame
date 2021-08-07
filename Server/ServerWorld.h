#ifndef _SERVER_WORLD_H_
#define _SERVER_WORLD_H_

#include "PlayerManager.h"
#include "ServerConnection.h"

class ServerWorld
{
public:
    ServerWorld();
    virtual ~ServerWorld();

    bool Init();
    void UnInit();

    void Run();
    void Quit();

private:
    bool LoadConfig();

public:
    PlayerManager    m_PlayerManager;
    ServerConnection m_Connection;

private:
    char m_szIP[_NAME_LEN];
    int m_nPort;
    bool m_bQuitFlag;
};

extern ServerWorld* g_pServer;
#endif