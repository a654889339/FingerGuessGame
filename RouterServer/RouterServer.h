#ifndef _ROUTER_SERVER_H_
#define _ROUTER_SERVER_H_

class RouterServer
{
public:
    RouterServer();
    virtual ~RouterServer();

    bool Init();
    void UnInit();

    void Run();
    void Quit();

};

extern RouterServer* g_pRouterServer;

#endif