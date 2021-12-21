#ifndef _CLIENT_ACCOUNT_SERVER_AGENT_H_
#define _CLIENT_ACCOUNT_SERVER_AGENT_H_

#include "TcpClient.h"
#include "CLIENT_ACCOUNT_SERVER_PROTOCOL.h"

class ASAgent : public TcpClient
{
public:
    ASAgent();
    virtual ~ASAgent();

    bool Init();
    void UnInit();

    void Active();

    void SetLogin(bool bLoginFlag);

private:
    void ProcessPackage(BYTE* pbyData, size_t uDataLen);
    void ConnectionLost();

    void OnAS2CLoginRespond(BYTE* pbyData, size_t uDataLen);



private:
    typedef void (ASAgent::* PROCESS_PROTOCOL_FUNC)(BYTE* pbyData, size_t uSize);
    PROCESS_PROTOCOL_FUNC   m_ProcessProtocolFuns[eas2c_end];
    int                     m_nProtocolSize[eas2c_end];

    bool m_bLoginFlag;
};

#endif