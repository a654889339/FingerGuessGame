#include "stdafx.h"
#include "ClientStateWaitToLogin.h"
#include "ClientWorld.h"

bool ClientStateWaitToLogin::Enter(ClientStateTrigger* pTrigger, ClientStateType eState)
{
    bool bResult  = false;
    bool bRetCode = false;

    JYLOG_PROCESS_ERROR(pTrigger);

    bRetCode = m_ASAgent.Init();
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_BOOL_END
}

bool ClientStateWaitToLogin::Leave(ClientStateTrigger* pTrigger, ClientStateType eState)
{
    bool bResult = false;

    JYLOG_PROCESS_ERROR(pTrigger);

    m_ASAgent.UnInit();

    JY_STD_BOOL_END
}

void ClientStateWaitToLogin::Active()
{
    m_ASAgent.Active();
}
