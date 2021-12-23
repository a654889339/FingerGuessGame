#ifndef _ACCOUNT_SERVER_CLIENT_AGENT_H_
#define _ACCOUNT_SERVER_CLIENT_AGENT_H_

#include "SplayTree.h"
#include "TcpServer.h"
#include "CLIENT_ACCOUNT_SERVER_PROTOCOL.h"
#include "AccountServerBase.h"

class ClientASServer : public TcpServer
{
public:
    ClientASServer();
    virtual ~ClientASServer();

    bool Init();
    void UnInit();

    void Active();

    bool DoAS2CLoginRespond(int nConnIndex, int nRetCode);

private:
    void ProcessPackage(int nConnIndex, BYTE* pbyData, size_t uDataLen);
    void NewConnection(int nConnIndex, int* pnIP, int nPort);
    void DisConnection(int nConnIndex);

    void OnC2ASLoginRequest(int nConnIndex, BYTE* pbyData, size_t uDataLen);

private:
    typedef void (ClientASServer::* PROCESS_PROTOCOL_FUNC)(int nConnIndex, BYTE* pbyData, size_t uSize);
    PROCESS_PROTOCOL_FUNC   m_ProcessProtocolFuns[eas2c_end];
    int                     m_nProtocolSize[eas2c_end];

    SplayTree<int, ConnectionInfo> m_ConnManager;

};

#endif