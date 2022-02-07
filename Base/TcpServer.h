#ifndef _TCP_SERVER_H_
#define _TCP_SERVER_H_
#include "TCPBase.h"

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

class TcpServer
{
public:
    TcpServer();
    virtual ~TcpServer();

    virtual bool IsEnable() final;
    virtual void Quit() final;

protected:
    virtual bool Bind(const char szIP[], int nPort) final;

    virtual void ProcessNetwork() final;
    virtual bool Send(int nConnIndex, void* pbyData, size_t uDataLen) final;
    virtual void Shutdown(int nConnIndex) final;
    virtual void* GetSendBuffer(size_t uDataLen) final;

    virtual void ProcessPackage(int nConnIndex, BYTE* pbyData, size_t uDataLen) = 0;
    virtual void NewConnection(int nConnIndex, int* pnIP, int nPort) = 0;
    virtual void DisConnection(int nConnIndex) = 0;

private:
    void AcceptConnection();
    RecvFD* GetClientFD(int nConnIndex);
    SOCKET GetClientSocket(int nConnIndex);
    bool IsAlive(int nConnIndex);

private:
    SOCKET m_Socket;
    bool m_bRunFlag;
    FD_SET  m_SocketReadSet;
    SOCKET m_nConnecFlag[MAX_ACCEPT_CONNECTION];

    char m_szRecvBuffer[MAX_RECV_BUFFER_SIZE];
    char m_szSendBuffer[MAX_RECV_BUFFER_SIZE];
    char m_szAPIBuffer[MAX_RECV_BUFFER_SIZE];

    typedef SplayTree<SOCKET, RecvFD> CLIENT_INDEX_MANAGER;
    CLIENT_INDEX_MANAGER m_ClientManager;
};
#endif