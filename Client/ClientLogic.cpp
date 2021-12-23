#include "stdafx.h"
#include "ClientLogic.h"

ClientLogic::ClientLogic()
{
    m_bQuitFlag = false;
    m_nTimeNow = 0;
    m_nGatePort = 0;

    memset(m_szGateIP, 0, sizeof(m_szGateIP));
}

ClientLogic::~ClientLogic()
{

}

bool ClientLogic::Init()
{
    bool bResult           = false;
    bool bRetCode          = false;
    bool bControlInitFlag  = false;
    bool bStateMgrInitFlag = false;

    m_nTimeNow = time(NULL);

    bRetCode = LoadConfig();
    JYLOG_PROCESS_ERROR(bRetCode);

    bRetCode = m_Control.Init();
    JYLOG_PROCESS_ERROR(bRetCode);
    bControlInitFlag = true;

    bRetCode = m_ClientStateManager.Init();
    JYLOG_PROCESS_ERROR(bRetCode);
    bStateMgrInitFlag = true;

    bResult = true;
Exit0:
    if (!bResult)
    {
        if (bStateMgrInitFlag)
        {
            m_ClientStateManager.Init();
            bStateMgrInitFlag = false;
        }

        if (bControlInitFlag)
        {
            m_Control.UnInit();
            bControlInitFlag = false;
        }
    }
    return bResult;
}

void ClientLogic::UnInit()
{
    m_ClientStateManager.UnInit();
    m_Control.UnInit();
}

void ClientLogic::Run()
{
    while (true)
    {
        m_nTimeNow = time(NULL);

        JY_PROCESS_ERROR(!CheckQuitComplete());

        m_Control.Active();
        m_ClientStateManager.Active();

        Sleep(10);
    }

    JY_STD_VOID_END
}

void ClientLogic::Quit()
{
    m_bQuitFlag = true;
    m_ClientStateManager.UnInit();
}

// Private
bool ClientLogic::CheckQuitComplete()
{
    bool bResult = false;

    JY_PROCESS_ERROR(m_bQuitFlag);
    JY_PROCESS_ERROR(!m_Connection.IsEnable());

    JY_STD_BOOL_END;
}

bool ClientLogic::LoadConfig()
{
    bool bResult = false;
    bool bRetCode = false;

    printf("[ClientWorld] Input your name:\n");
    while (true)
    {
        scanf("%s", m_szPlayerName);
        m_szPlayerName[sizeof(m_szPlayerName) - 1] = '\0';
        bRetCode = CheckNickName(m_szPlayerName);
        if (bRetCode)
        {
            break;
        }
        else
            puts("含有非法字符，请重新输入.");
    }

    JY_STD_BOOL_END
}