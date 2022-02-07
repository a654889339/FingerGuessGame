#include "stdafx.h"
#include "RouterServer.h"

RouterServer* g_pRouterServer = NULL;

#ifdef WIN32
bool WINAPI ConsoleHandlerRoutine(DWORD dwCtrlType)
{
    if (g_pRouterServer)
    {
        printf("Receive quit signal from console !\n");
        g_pRouterServer->Quit();
    }
    return true;
}
#endif

int main(int argc, char* argv[])
{
    bool    bResult   = false;
    bool    bRetCode  = false;
    bool    bInitFlag = false;

    g_pRouterServer = new RouterServer();
    JYLOG_PROCESS_ERROR(g_pRouterServer);

    bRetCode = g_pRouterServer->Init();
    JYLOG_PROCESS_ERROR(bRetCode);
    bInitFlag = true;

    g_pRouterServer->Run();

    bResult = true;
Exit0:
    if (bInitFlag)
    {
        g_pRouterServer->UnInit();
        bInitFlag = false;
    }

    if (g_pRouterServer)
    {
        delete g_pRouterServer;
        g_pRouterServer = NULL;
    }

    return 0;
}
