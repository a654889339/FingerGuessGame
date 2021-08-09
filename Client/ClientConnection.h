#ifndef _CLIENT_CONNECTION_H_
#define _CLIENT_CONNECTION_H_

#include "TcpClient.h"
#include "Protocol.h"

class ClientConnection : public TcpClient
{
public:
    ClientConnection();
    virtual ~ClientConnection();

    bool Init(const char szIP[], int nPort);
    void UnInit();

    void Active();
    void DisConnect();

    bool DoC2SPingRequest();
    bool DoC2SQuitNotify();
    bool DoC2SLoginRequest();
    bool DoC2SApplyAllPlayerRequest();
    bool DoCreateGameRequest();
    bool DoJoinGameRequest(const char szName[]);
    bool DoC2SPlayGameNotify(GameOperateCode eCode);

private:
    void OnS2CPingRespond(BYTE* pbyData, size_t uSize);
    void OnS2CLoginRespond(BYTE* pbyData, size_t uSize);
    void OnS2CApplyAllPlayerRespond(BYTE* pbyData, size_t uSize);
    void OnS2CCreateGameRespond(BYTE* pbyData, size_t uSize);
    void OnS2CJoinGameRespond(BYTE* pbyData, size_t uSize);
    void OnS2CPlayerJoinGameRespond(BYTE* pbyData, size_t uSize);
    void OnS2CGameResultNotify(BYTE* pbyData, size_t uSize);

    void ProcessPackage(byte* pbyData, size_t uDataLen);
    void ConnectionLost();

private:
    typedef void (ClientConnection::* PROCESS_PROTOCOL_FUNC)(BYTE* pbyData, size_t uSize);
    PROCESS_PROTOCOL_FUNC   m_ProcessProtocolFuns[s2c_end];
    int                     m_nProtocolSize[s2c_end];

    time_t m_nNextPingTime;
};
#endif