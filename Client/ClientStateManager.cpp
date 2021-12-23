#include "stdafx.h"
#include "ClientStateManager.h"

ClientStateManager::ClientStateManager()
{
    for (int i = ecst_begin; i < ecst_end; i++)
    {
        m_pszState[i] = &m_BaseState[i];
        m_BaseState[i].m_eState = (ClientStateType)i;
    }

    m_pszState[ecst_wait_to_login] = &m_WaitToLogin;
    m_State.m_eState = ecst_init_client;
}

ClientStateManager::~ClientStateManager()
{

}


bool ClientStateManager::Init()
{
    bool bResult = false;

    JY_STD_BOOL_END
}

void ClientStateManager::UnInit()
{
    Set(ecst_init_client);
}

void ClientStateManager::Active()
{
    m_State.Active();
}

bool ClientStateManager::Set(ClientStateType eState)
{
    bool                bResult = false;
    bool                bRetCode = false;
    ClientStateTrigger* pTrigger = NULL;

    JYLOG_PROCESS_ERROR(eState >= ecst_begin && eState < ecst_end);

    // 调用旧状态的Leave
    pTrigger = m_pszState[m_State.m_eState];
    JYLOG_PROCESS_ERROR(pTrigger);

    bRetCode = pTrigger->Leave(&m_State, eState);
    JYLOG_PROCESS_ERROR(bRetCode);

    // 调用新状态的Enter
    pTrigger = m_pszState[eState];
    JYLOG_PROCESS_ERROR(pTrigger);

    bRetCode = pTrigger->Enter(&m_State, m_State.m_eState);
    JYLOG_PROCESS_ERROR(bRetCode);

    // 设置新状态
    m_State.m_eState = eState;

    JY_STD_BOOL_END
}
