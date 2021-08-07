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

    bool DoS2CHandshakeRequest();

private:
    void OnS2CHandshakeRespond(BYTE* pbyData, size_t uSize);

    void ProcessPackage(byte* pbyData, size_t uDataLen);
    void ConnectionLost();


private:
    typedef void (ClientConnection::* PROCESS_PROTOCOL_FUNC)(BYTE* pbyData, size_t uSize);
    PROCESS_PROTOCOL_FUNC   m_ProcessProtocolFuns[s2c_end];
    int                     m_nProtocolSize[s2c_end];
};
#endif