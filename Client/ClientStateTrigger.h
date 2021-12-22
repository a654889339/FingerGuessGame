#ifndef _CLIENT_STATE_TRIGGER_H_
#define _CLIENT_STATE_TRIGGER_H_

enum ClientStateType
{
    ecst_begin = 0,
    ecst_invalid = ecst_begin,

    ecst_wait_to_login, // ��¼����
    ecst_wait_to_connect_gate, // ��¼�ɹ�����ʼ����Gate

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
    virtual void Active() {}

    ClientStateType m_eState;
};

#endif