#ifndef _CLIENT_STATE_MANAGER_H_
#define _CLIENT_STATE_MANAGER_H_

#include "ClientStateTrigger.h"
#include "ClientStateWaitToLogin.h"
#include "ClientStateWaitToConnectGate.h"
#include "ClientStatePlaying.h"

class ClientStateManager
{
public:
    ClientStateManager();
    virtual ~ClientStateManager();

    bool Init();
    void UnInit();
    void Active();

    bool Set(ClientStateType eState);

    ClientStateType Get(){return m_State.m_eState;}

private:
    ClientStateTrigger            m_State;
    ClientStateTrigger*           m_pszState[ecst_end];
    ClientStateTrigger            m_BaseState[ecst_end];

    ClientStateWaitToLogin        m_WaitToLogin;
    ClientStateWaitToConnectGate  m_WaitToConnectGate;
    ClientStatePlaying            m_Playing;
};


#endif