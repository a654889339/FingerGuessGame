#ifndef _GATE_GAME_SERVER_AGENT_H_
#define _GATE_GAME_SERVER_AGENT_H_

#include "TcpClient.h"

class GateGSAgent : public TcpClient
{
    GateGSAgent();
    virtual ~GateGSAgent();

    bool Init();
    void UnInit();

    void Active();

private:
    void ProcessPackage(BYTE* pbyData, size_t uDataLen);
    void ConnectionLost();

};

#endif