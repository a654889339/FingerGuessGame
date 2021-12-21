#ifndef _ACCOUNT_SERVER_H_
#define _ACCOUNT_SERVER_H_

#include "ASClientAgent.h"
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
    ASClientAgent m_ClientAgent;
    ClientManager m_ClientManager;
};

extern AccountServer* g_pAccountServer;

#endif