#include "stdafx.h"
#include "ClientStateTriggerWaitToLogin.h"
#include "ClientWorld.h"

bool ClientStateTriggerWaitToLogin::Enter(ClientStateTrigger* pTrigger, ClientStateType eState)
{
    bool bResult  = false;
    bool bRetCode = false;
    JYLOG_PROCESS_ERROR(pTrigger);

    bRetCode = g_pClient->m_ASAgent.Init();
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_BOOL_END
}

bool ClientStateTriggerWaitToLogin::Leave(ClientStateTrigger* pTrigger, ClientStateType eState)
{
    bool bResult = false;

    JYLOG_PROCESS_ERROR(pTrigger);

    g_pClient->m_ASAgent.UnInit();

    JY_STD_BOOL_END
}

void ClientStateTriggerWaitToLogin::Active()
{
    g_pClient->m_ASAgent.Active();
}
