#ifndef _CLIENT_STATE_TRIGGER_WAIT_TO_LOGIN_H_
#define _CLIENT_STATE_TRIGGER_WAIT_TO_LOGIN_H_

#include "ClientStateTrigger.h"

class ClientStateTriggerWaitToLogin : public ClientStateTrigger
{
public:
    ClientStateTriggerWaitToLogin() {m_eState = ecst_wait_to_login;}

    bool Enter(ClientStateTrigger* pTrigger, ClientStateType eState);
    bool Leave(ClientStateTrigger* pTrigger, ClientStateType eState);
    void Active();
};


#endif