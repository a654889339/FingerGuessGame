#ifndef _CLIENT_WORLD_H_
#define _CLIENT_WORLD_H_

#include "ClientConnection.h"

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
    ClientConnection m_Connection;

private:
    char m_szIP[_NAME_LEN];
    int  m_nPort;
    bool m_bQuitFlag;
};

extern ClientWorld* g_pClient;
#endif