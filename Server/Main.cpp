#include "stdafx.h"
#include "ServerWorld.h"

ServerWorld* g_pServer = NULL;

#ifdef WIN32
BOOL WINAPI ConsoleHandlerRoutine(DWORD dwCtrlType)
{
    if (g_pServer)
    {
        printf("Receive quit signal from console !\n");
        g_pServer->Quit();
    }
    return true;
}
#endif

int main(int argc, char* argv[])
{
    bool    bResult = false;
    BOOL    bRetCode = false;
    BOOL    bClientInitFlag = false;

    g_pServer = new ServerWorld();
    JYLOG_PROCESS_ERROR(g_pServer);

    bRetCode = g_pServer->Init();
    JYLOG_PROCESS_ERROR(bRetCode);
    bClientInitFlag = true;

    g_pServer->Run();

    bResult = true;
Exit0:
    if (bClientInitFlag)
    {
        g_pServer->UnInit();
        bClientInitFlag = false;
    }

    if (g_pServer)
    {
        delete g_pServer;
        g_pServer = NULL;
    }

    return 0;
}
