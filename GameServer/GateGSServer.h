#ifndef _SERVER_CONNECTION_H_
#define _SERVER_CONNECTION_H_

#include "TcpServer.h"
#include "CLIENT_GAME_SERVER_PROTOCOL.h"

#include "ConnectionSystem.h"

#include "ServerBase.h"
#include "Player.h"

class GateGSServer : public TcpServer
{
public:
    GateGSServer();
    virtual ~GateGSServer();

    bool Init(const char szIP[], int nPort);
    void UnInit();

    void Active();

    bool DoS2CPingRespond(int nConnIndex);
    bool DoS2CLoginRespond(int nConnIndex, int nRetCode);

private:
    void OnC2SPingRequest(int nConnIndex, BYTE* pbyData, size_t uDataLen);
    void OnC2SQuitNotify(int nConnIndex, BYTE* pbyData, size_t uDataLen);
    void OnC2SLoginRequest(int nConnIndex, BYTE* pbyData, size_t uDataLen);

    void ProcessPackage(int nConnIndex, BYTE* pbyData, size_t uDataLen);
    void NewConnection(int nConnIndex, int* pnIP, int nPort);
    void DisConnection(int nConnIndex);

private:
    typedef void (GateGSServer::* PROCESS_PROTOCOL_FUNC)(int nConnIndex, BYTE* pbyData, size_t uSize);
    PROCESS_PROTOCOL_FUNC   m_ProcessProtocolFuns[c2s_end];
    int                     m_nProtocolSize[c2s_end];

    char                    m_szTempBuffer[MAX_RECV_BUFFER_SIZE];

    ComponentList<ConnectionComponent> m_ConnectionCList;
    ConnectionSystem                   m_ConnectionSystem;
};

#endif