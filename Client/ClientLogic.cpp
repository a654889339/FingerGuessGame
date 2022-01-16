#include "stdafx.h"
#include "ClientLogic.h"

CLIENT_LOGIC_DLL_API IClientLogic* CreateClientLogic()
{
    IClientLogic* pResult = NULL;
    bool          bRetCode = false;

#ifdef _CLIENT
    pResult = (IClientLogic*)new ClientLogic();
#else
    pResult = new IClientLogic();
#endif
    JYLOG_PROCESS_ERROR(pResult);

    bRetCode = pResult->Init();
    if (!bRetCode)
    {
        delete pResult;
        pResult = NULL;
        JYLOG_PROCESS_ERROR(false);
    }

Exit0:
    return pResult;
}

CLIENT_LOGIC_DLL_API void DestroyClientLogic(IClientLogic* pClientLogic)
{
    JYLOG_PROCESS_ERROR(pClientLogic);

    pClientLogic->UnInit();

    delete pClientLogic;
    pClientLogic = NULL;

    JY_STD_VOID_END
}

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
            m_ClientStateManager.UnInit();
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


    JY_STD_BOOL_END
}
