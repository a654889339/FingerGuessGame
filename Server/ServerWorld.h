#ifndef _SERVER_WORLD_H_
#define _SERVER_WORLD_H_

#include "SystemManager.h"

#include "PlayerManager.h"
#include "ServerConnection.h"
#include "DBManager.h"

class ServerWorld
{
public:
    ServerWorld();
    virtual ~ServerWorld();

    bool Init();
    void UnInit();

    void Run();
    void Quit();
    bool CheckQuitComplete();

private:
    bool LoadConfig();

public:
    PlayerManager    m_PlayerManager;
    ServerConnection m_Connection;
    DBManager        m_DB;
    SystemManager    m_SystemManager;

private:
    char m_szIP[_NAME_LEN];
    int m_nPort;
    bool m_bQuitFlag;


    char m_szDBIP[_NAME_LEN];
    int m_nDBPort;
    char m_szDBAccount[_NAME_LEN];
    char m_szDBPassward[_NAME_LEN];
    char m_szDBName[_NAME_LEN];
};

extern ServerWorld* g_pServer;
#endif