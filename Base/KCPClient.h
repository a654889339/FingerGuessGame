#ifndef _KCP_CLIENT_H_
#define _KCP_CLIENT_H_

#include "NetworkBase.h"

class KCPClient
{
public:
    KCPClient();
    virtual ~KCPClient();

    virtual bool Connect(const char szIP[], int nPort) final ;
    virtual void ProcessNetwork() final;
    virtual bool Send(void* pbyData, size_t uDataLen) final;

private:
    virtual void ProcessPackage(byte* pbyData, size_t uDataLen) = 0;
    virtual void ConnectionLost() = 0;


private:
    char    m_szIP[_NAME_LEN];
    int     m_nPort;

    char m_szRecvBuffer[MAX_RECV_BUFFER_SIZE];
    char m_szSendBuffer[MAX_RECV_BUFFER_SIZE];
};


#endif
