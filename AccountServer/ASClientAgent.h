#ifndef _ACCOUNT_SERVER_CLIENT_AGENT_H_
#define _ACCOUNT_SERVER_CLIENT_AGENT_H_

#include "TcpServer.h"

class ASClientAgent : public TcpServer
{
public:
    ASClientAgent();
    virtual ~ASClientAgent();

    bool Init();
    void UnInit();

    void Run();

    void ProcessPackage(int nConnIndex, byte* pbyData, size_t uDataLen);
    void NewConnection(int nConnIndex, const char szIP[], int nPort);
    void DisConnection(int nConnIndex);
};

#endif