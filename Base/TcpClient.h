#ifndef _TCP_CLIENT_H_
#define _TCP_CLIENT_H_

#include "NetworkBase.h"

class TcpClient
{
public:
    TcpClient();
    virtual ~TcpClient();

    virtual bool Connect(const char szIP[], int nPort) final ;
    virtual void ProcessNetwork();

protected:
    virtual void ProcessPackage(byte* pbyData, size_t uDataLen) = 0;
    virtual void DisConnection() = 0;

    bool HaveFullPackage();

private:
    bool m_bRunFlag;
    SOCKET m_Socket;

    typedef CycleQueue<char, MAX_RECV_BUFFER_SIZE> RECV_QUEUE;
    RECV_QUEUE  m_RecvQueue;

    char m_szRecvBuffer[MAX_RECV_BUFFER_SIZE];
    bool m_bHaveProtoSize;
    size_t m_uProtoSize;
};

#endif