#ifndef _BASE_ROUTER_MODULE_AGENT_H_
#define _BASE_ROUTER_MODULE_AGENT_H_

#include "TcpClient.h"
#include "RouterModuleBase.h"
#include "JYThread.h"
#include "LockQueue.h"

class RouterModuleAgent : public TcpClient
{
public:
    RouterModuleAgent();
    virtual ~RouterModuleAgent();

    bool Init(RouterModuleType eType);
    void UnInit();

    bool Recv(size_t uLimitSize, BYTE* &pbyData, size_t* puDataLen, RouterModuleType* peType, uint16_t* pnProtocolID);
    bool SendToModule(RouterModuleType eType, uint16_t nProtocolID, BYTE* pbyData, size_t uDataLen);

private:
    static void WorkThread(void* pvParam);
    void Run();
    void ProcessPackage(BYTE* pbyData, size_t uDataLen);
    void ConnectionLost();
    void SendFlush();

private:
    RouterModuleType m_eType;
    JYThread         m_Thread;
    LockQueue        m_RecvQueue; // routerserver --> agent
    LockQueue        m_SendQueue;
    BYTE             m_byThreadBuffer[MAX_INTERNAL_NETWORK_PROTOCOL_SIZE];
    BYTE             m_byMainBuffer[MAX_INTERNAL_NETWORK_PROTOCOL_SIZE];
};

#endif