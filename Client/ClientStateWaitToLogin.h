#ifndef _CLIENT_STATE_WAIT_TO_LOGIN_H_
#define _CLIENT_STATE_WAIT_TO_LOGIN_H_

#include "ClientStateTrigger.h"
#include "ClientASAgent.h"

// 进入此状态就启用与AS的连接，并等到登录回包，修改状态(ASAgent::OnAS2CLoginRespond)
class ClientStateWaitToLogin : public ClientStateTrigger
{
public:
    ClientStateWaitToLogin() {m_eState = ecst_wait_to_login;}

    bool Enter(ClientStateTrigger* pTrigger, ClientStateType eState);
    bool Leave(ClientStateTrigger* pTrigger, ClientStateType eState);
    void Active();

private:
    ClientASAgent            m_ASAgent;
};


#endif