#ifndef _ROUTER_SERVER_H_
#define _ROUTER_SERVER_H_

#include "RouterModuleMgr.h"

class RouterServer
{
public:
    RouterServer();
    virtual ~RouterServer();

    bool Init();
    void UnInit();

    void Run();
    void Quit();


private:
    RouterModuleMgr m_ModuleMgr;
};

extern RouterServer* g_pRouterServer;

#endif