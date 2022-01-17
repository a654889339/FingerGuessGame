#ifndef _CLIENT_LOGIC_H_
#define _CLIENT_LOGIC_H_

#include "DLL\IClientLogic.h"
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

private:
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
    bool m_bQuitFlag;
};
#ifdef CLIENT_LOGIC_DLL_API // .dll
static ClientLogic* g_pClient;
#else // .exe
extern ClientLogic* g_pClient;
#endif


#endif