#ifndef _SERVER_CONNECTION_H_
#define _SERVER_CONNECTION_H_

#include "TcpServer.h"
#include "Protocol.h"

class ServerConnection : public TcpServer
{
public:
    ServerConnection();
    virtual ~ServerConnection();

    bool Init(const char szIP[], int nPort);
    void UnInit();

    void Active();

    bool DoS2CHandshakeRespond(int nConnIndex, bool bSuccess);

private:
    void OnC2SHandshakeRequest(int nConnIndex, byte* pbyData, size_t uDataLen);

    void ProcessPackage(int nConnIndex, byte* pbyData, size_t uDataLen);
    void NewConnection(int nConnIndex, const char szIP[], int nPort);
    void DisConnection(int nConnIndex);

private:
    typedef void (ServerConnection::* PROCESS_PROTOCOL_FUNC)(int nConnIndex, BYTE* pbyData, size_t uSize);
    PROCESS_PROTOCOL_FUNC   m_ProcessProtocolFuns[c2s_end];
    int                     m_nProtocolSize[c2s_end];
};

#endif