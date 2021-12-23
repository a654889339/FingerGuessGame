#ifndef _CLIENT_STATE_WAIT_TO_LOGIN_H_
#define _CLIENT_STATE_WAIT_TO_LOGIN_H_

#include "ClientStateTrigger.h"
#include "ASAgent.h"

// �����״̬��������AS�����ӣ����ȵ���¼�ذ����޸�״̬(ASAgent::OnAS2CLoginRespond)
class ClientStateWaitToLogin : public ClientStateTrigger
{
public:
    ClientStateWaitToLogin() {m_eState = ecst_wait_to_login;}

    bool Enter(ClientStateTrigger* pTrigger, ClientStateType eState);
    bool Leave(ClientStateTrigger* pTrigger, ClientStateType eState);
    void Active();

private:
    ASAgent            m_ASAgent;
};


#endif