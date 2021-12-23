#ifndef _CLIENT_STATE_MANAGER_H_
#define _CLIENT_STATE_MANAGER_H_

#include "ClientStateTrigger.h"
#include "ClientStateWaitToLogin.h"

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
    ClientStateTrigger            m_State; // 客户端状态
    ClientStateTrigger*           m_pszState[ecst_end];
    ClientStateTrigger            m_BaseState[ecst_end]; // 避免状态的指针为空
    ClientStateWaitToLogin m_WaitToLogin;
};


#endif