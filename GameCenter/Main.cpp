#include "stdafx.h"
#include "GameCenter.h"

GameCenter* g_pGameCenter = NULL;

#ifdef WIN32
BOOL WINAPI ConsoleHandlerRoutine(DWORD dwCtrlType)
{
    if (g_pGameCenter)
    {
        printf("Receive quit signal from console !\n");
        g_pGameCenter->Quit();
    }
    return true;
}
#endif

int main(int argc, char* argv[])
{
    bool    bResult   = false;
    bool    bRetCode  = false;
    bool    bInitFlag = false;

    g_pGameCenter = new GameCenter();
    JYLOG_PROCESS_ERROR(g_pGameCenter);

    bRetCode = g_pGameCenter->Init();
    JYLOG_PROCESS_ERROR(bRetCode);
    bInitFlag = true;

    g_pGameCenter->Run();

    bResult = true;
Exit0:
    if (bInitFlag)
    {
        g_pGameCenter->UnInit();
        bInitFlag = false;
    }

    if (g_pGameCenter)
    {
        delete g_pGameCenter;
        g_pGameCenter = NULL;
    }

    return 0;
}
