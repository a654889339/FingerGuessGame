#ifndef _CLIENT_CONNECTION_H_
#define _CLIENT_CONNECTION_H_

#include "TcpClient.h"
#include "ClientBase.h"
#include "CLIENT_GAME_SERVER_PROTOCOL.h"

class ClientGateAgent : public TcpClient
{
public:
    ClientGateAgent();
    virtual ~ClientGateAgent();

    bool Init();
    void UnInit();

    void Active();
    void DisConnect();

    bool DoC2SPingRequest();
    bool DoC2SQuitNotify();
    bool DoC2SLoginRequest();

private:
    void OnS2CPingRespond(BYTE* pbyData, size_t uSize);
    void OnS2CLoginRespond(BYTE* pbyData, size_t uSize);

    void ProcessPackage(BYTE* pbyData, size_t uDataLen);
    void ConnectionLost();

private:
    typedef void (ClientGateAgent::* PROCESS_PROTOCOL_FUNC)(BYTE* pbyData, size_t uSize);
    PROCESS_PROTOCOL_FUNC   m_ProcessProtocolFuns[s2c_end];
    int                     m_nProtocolSize[s2c_end];

    time_t m_nNextPingTime;
    time_t m_nNextReconnectTime;
};
#endif