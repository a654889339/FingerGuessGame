#ifndef _CLIENT_STATE_WAIT_TO_CONNECT_GATE_H_
#define _CLIENT_STATE_WAIT_TO_CONNECT_GATE_H_

#include "ClientStateTrigger.h"

class ClientStateWaitToConnectGate : public ClientStateTrigger
{
public:
    ClientStateWaitToConnectGate() {m_eState = ecst_wait_to_connect_gate;}

    bool Enter(ClientStateTrigger* pTrigger, ClientStateType eState);
    void Active();

};

#endif