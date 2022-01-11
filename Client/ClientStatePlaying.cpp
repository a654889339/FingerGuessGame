#include "stdafx.h"
#include "ClientStatePlaying.h"
#include "ClientLogic.h"

bool ClientStatePlaying::Enter(ClientStateTrigger* pTrigger, ClientStateType eState)
{
    bool bResult = false;

    JYLOG_PROCESS_ERROR(pTrigger);

    m_GamePlay.Init();

    JY_STD_BOOL_END
}

bool ClientStatePlaying::Leave(ClientStateTrigger* pTrigger, ClientStateType eState)
{
    bool bResult = false;

    JYLOG_PROCESS_ERROR(pTrigger);

    m_GamePlay.UnInit();
    g_pClient->m_Connection.DisConnect();

    JY_STD_BOOL_END
}


void ClientStatePlaying::Active()
{
    g_pClient->m_Connection.Active();
    m_GamePlay.Active();

    Sleep(10);
}