#include "stdafx.h"
#include "ClientStateWaitToConnectGate.h"
#include "ClientWorld.h"

bool ClientStateWaitToConnectGate::Enter(ClientStateTrigger* pTrigger, ClientStateType eState)
{
    bool bResult  = false;
    bool bRetCode = false;

    JYLOG_PROCESS_ERROR(pTrigger);

    bRetCode = g_pClient->m_Connection.Init();
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_BOOL_END
}

void ClientStateWaitToConnectGate::Active()
{
    g_pClient->m_Connection.Active();
}
