#ifndef _SERVER_CONNECTION_H_
#define _SERVER_CONNECTION_H_

#include "ServerBase.h"
#include "TcpServer.h"
#include "Protocol.h"
#include "Player.h"

class ServerConnection : public TcpServer
{
public:
    ServerConnection();
    virtual ~ServerConnection();

    bool Init(const char szIP[], int nPort);
    void UnInit();

    void Active();

    bool DoS2CPingRespond(int nConnIndex);
    bool DoS2CLoginRespond(int nConnIndex, int nRetCode);

private:
    void OnC2SPingRequest(int nConnIndex, byte* pbyData, size_t uDataLen);
    void OnC2SQuitNotify(int nConnIndex, byte* pbyData, size_t uDataLen);
    void OnC2SLoginRequest(int nConnIndex, byte* pbyData, size_t uDataLen);

    void ProcessPackage(int nConnIndex, byte* pbyData, size_t uDataLen);
    void NewConnection(int nConnIndex, const char szIP[], int nPort);
    void DisConnection(int nConnIndex);

private:
    typedef void (ServerConnection::* PROCESS_PROTOCOL_FUNC)(int nConnIndex, BYTE* pbyData, size_t uSize);
    PROCESS_PROTOCOL_FUNC   m_ProcessProtocolFuns[c2s_end];
    int                     m_nProtocolSize[c2s_end];

    char                    m_szTempBuffer[MAX_RECV_BUFFER_SIZE];

};

#endif