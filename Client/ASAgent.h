#ifndef _CLIENT_ACCOUNT_SERVER_AGENT_H_
#define _CLIENT_ACCOUNT_SERVER_AGENT_H_

#include "TcpClient.h"
#include "CLIENT_ACCOUNT_SERVER_PROTOCOL.h"

class ASAgent : public TcpClient
{
public:
    ASAgent();
    virtual ~ASAgent();

    bool Init();
    void UnInit();

    void Active();

    void SetLogin(bool bLoginFlag);

private:
    void ProcessPackage(byte* pbyData, size_t uDataLen);
    void ConnectionLost();



private:
    bool m_bLoginFlag;
};

#endif