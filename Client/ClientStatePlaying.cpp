#include "stdafx.h"
#include "ClientStatePlaying.h"
#include "ClientWorld.h"

bool ClientStatePlaying::Enter(ClientStateTrigger* pTrigger, ClientStateType eState)
{
    bool bResult = false;

    JYLOG_PROCESS_ERROR(pTrigger);

    JY_STD_BOOL_END
}

bool ClientStatePlaying::Leave(ClientStateTrigger* pTrigger, ClientStateType eState)
{
    bool bResult = false;

    JYLOG_PROCESS_ERROR(pTrigger);

    g_pClient->m_Connection.DisConnect();

    JY_STD_BOOL_END
}


void ClientStatePlaying::Active()
{
    g_pClient->m_Connection.Active();

    // Ö¡¿ØÖÆ
    Sleep(10);
}