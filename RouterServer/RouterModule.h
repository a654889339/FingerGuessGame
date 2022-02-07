#ifndef _ROUTER_MODULE_H_
#define _ROUTER_MODULE_H_

#include "RouterModuleBase.h"
#include "TcpServer.h"
#include "JYThread.h"
#include "LockQueue.h"

// for accountserver, gamecenter or rankserver, chat server and so on.
class RouterModule : public TcpServer
{
public:
    RouterModule();
    virtual ~RouterModule();

    // Chat0, Chat1, Chat2. Chat2:eType=Chat,nConnIndex=2
    bool Init(RouterModuleType eType, const char szIP[], int nPort);
    void UnInit();

    IJYBuffer* Recv();
    bool SendToModule(IJYBuffer* piBuffer);

    RouterModuleType GetType() { return m_eModuleType; }

private:
    static void WorkThread(void* pvParam);
    void Run();
    void ProcessPackage(int nConnIndex, BYTE* pbyData, size_t uDataLen);
    void NewConnection(int nConnIndex, int* pnIP, int nPort);
    void DisConnection(int nConnIndex);
    void SendFlush();

private:
    RouterModuleType m_eModuleType;
    int              m_nConnIndex;
    char             m_szIP[64];
    int              m_nPort;
    JYThread         m_Thread;
    LockQueue        m_RecvQueue; // chat, gc, rank, account -> routerserver
    LockQueue        m_SendQueue;
    byte             m_byTempSize[MAX_INTERNAL_NETWORK_PROTOCOL_SIZE];
};

#endif