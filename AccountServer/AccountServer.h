#ifndef _ACCOUNT_SERVER_H_
#define _ACCOUNT_SERVER_H_

#include "ClientASServer.h"
#include "ClientManager.h"

class AccountServer
{
public:
    AccountServer();
    virtual ~AccountServer();

    bool Init();
    void UnInit();

    void Run();
    void Quit();


public:
    ClientASServer m_ClientAgent;
    ClientManager m_ClientManager;
};

extern AccountServer* g_pAccountServer;

#endif