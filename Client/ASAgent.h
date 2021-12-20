#ifndef _CLIENT_ACCOUNT_SERVER_AGENT_H_
#define _CLIENT_ACCOUNT_SERVER_AGENT_H_

#include "TcpClient.h"

class ASAgent : public TcpClient
{
public:
    ASAgent();
    virtual ~ASAgent();

    bool Init();
    void UnInit();

    void Active();

    void ProcessPackage(byte* pbyData, size_t uDataLen);
    void ConnectionLost();
};

#endif