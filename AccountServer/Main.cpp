#include "stdafx.h"
#include "AccountServer.h"

AccountServer* g_pAccountServer = NULL;

#ifdef WIN32
BOOL WINAPI ConsoleHandlerRoutine(DWORD dwCtrlType)
{
    if (g_pAccountServer)
    {
        printf("Receive quit signal from console !\n");
        g_pAccountServer->Quit();
    }
    return true;
}
#endif

int main(int argc, char* argv[])
{
    bool    bResult   = false;
    bool    bRetCode  = false;
    bool    bInitFlag = false;

    g_pAccountServer = new AccountServer();
    JYLOG_PROCESS_ERROR(g_pAccountServer);

    bRetCode = g_pAccountServer->Init();
    JYLOG_PROCESS_ERROR(bRetCode);
    bInitFlag = true;

    g_pAccountServer->Run();

    bResult = true;
Exit0:
    if (bInitFlag)
    {
        g_pAccountServer->UnInit();
        bInitFlag = false;
    }

    if (g_pAccountServer)
    {
        delete g_pAccountServer;
        g_pAccountServer = NULL;
    }

    return 0;
}
