#ifndef _ACCOUNT_SERVER_H_
#define _ACCOUNT_SERVER_H_

#include "ASClientAgent.h"

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

};

extern AccountServer* g_pAccountServer;

#endif