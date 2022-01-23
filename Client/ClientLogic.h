#ifndef _CLIENT_LOGIC_H_
#define _CLIENT_LOGIC_H_

#include "IClientLogic.h"
#include "CLIENT_GAME_ENGINE_PROTOCOL.h"
// Base
#include "LockQueue.h"

#include "ClientControl.h"
#include "ClientGateAgent.h"
#include "ClientBase.h"
#include "ClientStateManager.h"

class ClientLogic : public IClientLogic
{
public:
    ClientLogic();
    virtual ~ClientLogic();

    bool Init();
    void UnInit();

    void Run();
    void Quit();

    // push engine-->client message to queue
    // the reason why use PushE2C function instead of operating m_E2CQueue directly is
    // to make static easily.
    bool PushE2C(BYTE* pbyData, size_t uDataLen);
    bool PopC2E(size_t uLimitSize, BYTE* pbyData, size_t* puDataLen);

private:
    // Client Logic operate
    bool PushC2E(BYTE* pbyData, size_t uDataLen);
    bool PopE2C(size_t uLimitSize, BYTE* pbyData, size_t* puDataLen);

    void ProcessEngineMsg();

    bool CheckQuitComplete();
    bool LoadConfig();

public:
    char m_szGateIP[_NAME_LEN];
    int  m_nGatePort;
    char m_szPlayerName[_NAME_LEN];

    time_t             m_nTimeNow;
    ClientStateManager m_ClientStateManager;
    ClientControl      m_Control;
    ClientGateAgent    m_Connection;

private:
    bool      m_bQuitFlag;
    LockQueue m_E2CQueue;
    LockQueue m_C2EQueue;
};

#ifdef CLIENT_LOGIC_DLL_API // .dll
static ClientLogic* g_pClient;
#else
extern ClientLogic* g_pClient;
#endif

#endif