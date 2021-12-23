#ifndef _CLIENT_STATE_PLAYING_H_
#define _CLIENT_STATE_PLAYING_H_

#include "ClientStateTrigger.h"

class ClientStatePlaying : public ClientStateTrigger
{
public:
    ClientStatePlaying() {m_eState = ecst_playing;}

    bool Enter(ClientStateTrigger* pTrigger, ClientStateType eState);
    bool Leave(ClientStateTrigger* pTrigger, ClientStateType eState);

    void Active();
};

#endif