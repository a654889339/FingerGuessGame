#ifndef _GATE_SERVER_H_
#define _GATE_SERVER_H_

class GateServer
{
public:
    GateServer();
    virtual ~GateServer();

    bool Init();
    void UnInit();

    void Run();
    void Quit();

};

extern GateServer* g_pGateServer;

#endif