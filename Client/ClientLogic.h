#ifndef _CLIENT_LOGIC_H_
#define _CLIENT_LOGIC_H_

#include "IClientLogic.h"
#include <thread>
#include <vector>
// Base
#include "LockQueue.h"
#include "JYThread.h"

#include "CLIENT_GAME_ENGINE_PROTOCOL.h"
#include "ClientControl.h"
#include "ClientGateAgent.h"
#include "ClientBase.h"
#include "ClientStateManager.h"


#define MAX_GAME_ENGINE_MSG_SIZE 4096

class ClientLogic : public IClientLogic
{
public:
    ClientLogic();
    virtual ~ClientLogic();

    bool        Init();
    void        UnInit();
    static void WorkThread(void* pvParam);
    void        Run();
    void        Quit();

    // push engine-->client message to queue
    // the reason why use PushE2C function instead of operating m_E2CQueue directly is
    // to make static easily.
    bool PushE2C(BYTE* pbyData, size_t uDataLen);
    bool PopC2E(size_t uLimitSize, BYTE* pbyData, size_t* puDataLen);

private:
    void OnLoginRequest(BYTE* pbyData, size_t uSize);

    // Client Logic operate
    bool PushC2E(BYTE* pbyData, size_t uDataLen);
    bool PopE2C(size_t uLimitSize, BYTE* pbyData, size_t* puDataLen);

    void ProcessEngineMsg();
    void ProcessPackage(BYTE* pbyData, size_t uDataLen);


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
    typedef void (ClientLogic::* PROCESS_PROTOCOL_FUNC)(BYTE* pbyData, size_t uSize);
    PROCESS_PROTOCOL_FUNC   m_ProcessProtocolFuns[eas2c_end];
    int                     m_nProtocolSize[eas2c_end];

    bool                     m_bQuitFlag;
    LockQueue                m_E2CQueue;
    LockQueue                m_C2EQueue;
    BYTE                     m_byEngineMsgBuffer[MAX_GAME_ENGINE_MSG_SIZE];

#ifdef CLIENT_LOGIC_DLL_API
    JYThread                 m_DLLThread;
#endif
};

static ClientLogic* g_pClient; // .dll
//.exe : extern ClientLogic* g_pClient;

#endif