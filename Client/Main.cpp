#include "stdafx.h"
#include "ClientWorld.h"

ClientWorld* g_pClient = NULL;

#ifdef WIN32
BOOL WINAPI ConsoleHandlerRoutine(DWORD dwCtrlType)
{
    if (g_pClient)
    {
        printf("Receive quit signal from console !\n");
        g_pClient->Quit();
    }
    return true;
}
#endif

int main(int argc, char* argv[])
{
    bool    bResult = false;
    BOOL    bRetCode = false;
    BOOL    bClientInitFlag = false;

    g_pClient = new ClientWorld();
    JYLOG_PROCESS_ERROR(g_pClient);

    bRetCode = g_pClient->Init();
    JYLOG_PROCESS_ERROR(bRetCode);
    bClientInitFlag = true;

    g_pClient->Run();

    bResult = true;
Exit0:
    if (bClientInitFlag)
    {
        g_pClient->UnInit();
        bClientInitFlag = false;
    }

    if (g_pClient)
    {
        delete g_pClient;
        g_pClient = NULL;
    }

    return 0;
}
