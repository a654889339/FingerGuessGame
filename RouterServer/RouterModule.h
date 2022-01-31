#ifndef _ROUTER_MODULE_H_
#define _ROUTER_MODULE_H_

#include "RouterModuleBase.h"
#include "TcpServer.h"
#include "JYThread.h"

// for accountserver, gamecenter or rankserver, chat server and so on.
class RouterModule : public TcpServer
{
public:
    RouterModule();
    virtual ~RouterModule();

    // Chat0, Chat1, Chat2. Chat2:eType=Chat,nConnIndex=2
    bool Init(RouterModuleType eType, int nConnIndex, const char szIP[], int nPort);
    void UnInit();
    static void WorkThread(void* pvParam);

    void Run();

private:
    void ProcessPackage(int nConnIndex, BYTE* pbyData, size_t uDataLen);
    void NewConnection(int nConnIndex, int* pnIP, int nPort);
    void DisConnection(int nConnIndex);


private:
    RouterModuleType m_eModuleType;
    int              m_nConnIndex;
    char             m_szIP[64];
    int              m_nPort;
    JYThread         m_Thread;
};


#endif