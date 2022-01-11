#ifndef _CLIENT_STATE_TRIGGER_H_
#define _CLIENT_STATE_TRIGGER_H_

#include "ClientBase.h"

enum ClientStateType
{
    ecst_begin = 0,
    ecst_init_client = ecst_begin,

    ecst_wait_to_login,
    ecst_wait_to_connect_gate,

    ecst_playing,

    ecst_end,
};

class ClientStateTrigger
{
public:
    // m_eState->eState
    virtual bool Enter(ClientStateTrigger* pTrigger, ClientStateType eState) {return true;}

    // eState->m_eState
    virtual bool Leave(ClientStateTrigger* pTrigger, ClientStateType eState) {return true;}
    virtual void Active() { Sleep(10); }

    ClientStateType m_eState;
};

#endif