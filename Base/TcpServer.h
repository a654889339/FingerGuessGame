#ifndef _TCP_SERVER_H_
#define _TCP_SERVER_H_

#include "NetworkBase.h"

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

class TcpServer
{
public:
    TcpServer();
    virtual ~TcpServer();

    virtual bool Bind(const char szIP[], int nPort) final;

    virtual void ProcessNetwork() final;
    virtual bool Send(int nConnIndex, void* pbyData, size_t uDataLen) final;

    virtual void ProcessPackage(int nConnIndex, byte* pbyData, size_t uDataLen) = 0;
    virtual void NewConnection(int nConnIndex, const char szIP[], int nPort) = 0;
    virtual void DisConnection(int nConnIndex) = 0;

private:
    RecvFD* GetRecvFD(int nConnIndex);

private:
    SOCKET m_Socket;
    bool m_bRunFlag;
    FD_SET  m_SocketReadSet;

    char m_szRecvBuffer[MAX_RECV_BUFFER_SIZE];
    RecvFD m_szRecvFD[MAX_ACCEPT_CONNECTION];
};
#endif