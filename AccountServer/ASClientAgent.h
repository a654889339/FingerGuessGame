#ifndef _ACCOUNT_SERVER_CLIENT_AGENT_H_
#define _ACCOUNT_SERVER_CLIENT_AGENT_H_

#include "SplayTree.h"
#include "TcpServer.h"
#include "CLIENT_ACCOUNT_SERVER_PROTOCOL.h"
#include "AccountServerBase.h"

class ASClientAgent : public TcpServer
{
public:
    ASClientAgent();
    virtual ~ASClientAgent();

    bool Init();
    void UnInit();

    void Active();

    bool DoAS2CLoginRespond(int nConnIndex, int nRetCode);

private:
    void ProcessPackage(int nConnIndex, BYTE* pbyData, size_t uDataLen);
    void NewConnection(int nConnIndex, int* pszIP, int nPort);
    void DisConnection(int nConnIndex);


    void OnC2ASLoginRequest(int nConnIndex, BYTE* pbyData, size_t uDataLen);

private:
    typedef void (ASClientAgent::* PROCESS_PROTOCOL_FUNC)(int nConnIndex, BYTE* pbyData, size_t uSize);
    PROCESS_PROTOCOL_FUNC   m_ProcessProtocolFuns[eas2c_end];
    int                     m_nProtocolSize[eas2c_end];

    SplayTree<int, ConnectionInfo> m_ConnManager;

};

#endif