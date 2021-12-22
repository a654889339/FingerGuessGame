#ifndef _CLIENT_STATE_MANAGER_H_
#define _CLIENT_STATE_MANAGER_H_

#include "ClientStateTrigger.h"
#include "ClientStateTriggerWaitToLogin.h"

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
    ClientStateTrigger            m_State; // �ͻ���״̬
    ClientStateTrigger*           m_pszState[ecst_end];
    ClientStateTrigger            m_BaseState[ecst_end]; // ����״̬��ָ��Ϊ��
    ClientStateTriggerWaitToLogin m_WaitToLogin;
};


#endif