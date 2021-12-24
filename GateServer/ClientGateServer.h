#ifndef _CLIENT_GATE_AGENT_H_
#define _CLIENT_GATE_AGENT_H_

#include "TcpServer.h"

class ClientGateServer : public TcpServer
{
    ClientGateServer();
    virtual ~ClientGateServer();

    bool Init();
    void UnInit();

    void Active();

private:
    void ProcessPackage(int nConnIndex, BYTE* pbyData, size_t uDataLen);
    void NewConnection(int nConnIndex, int* pszIP, int nPort);
    void DisConnection(int nConnIndex);

};

#endif