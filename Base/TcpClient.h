#ifndef _TCP_CLIENT_H_
#define _TCP_CLIENT_H_

#include "TCPBase.h"

class TcpClient
{
public:
    TcpClient();
    virtual ~TcpClient();

    virtual bool IsEnable() final;
    virtual void Quit() final;

protected:
    virtual bool Connect(const char szIP[], int nPort) final;
    virtual void ProcessNetwork() final;
    virtual bool Send(void* pbyData, size_t uDataLen) final;
    virtual void* GetSendBuffer(size_t uDataLen) final; // 给继承的子类发包时用，将待发送数据写进APIBuffer内。

    virtual void ProcessPackage(BYTE* pbyData, size_t uDataLen) = 0;
    virtual void ConnectionLost() = 0;

private:
    bool m_bRunFlag;
    SOCKET m_Socket;
    RecvFD m_RecvFD;

    char m_szRecvBuffer[MAX_RECV_BUFFER_SIZE];
    char m_szSendBuffer[MAX_RECV_BUFFER_SIZE];
    char m_szAPIBuffer[MAX_RECV_BUFFER_SIZE];
};

#endif