#include "stdafx.h"
#include "ClientLogic.h"

ClientLogic* g_pClient = NULL;

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
    bool    bResult   = false;
    bool    bRetCode  = false;
    bool    bInitFlag = false;

    g_pClient = new ClientLogic();
    JYLOG_PROCESS_ERROR(g_pClient);

    bRetCode = g_pClient->Init();
    JYLOG_PROCESS_ERROR(bRetCode);
    bInitFlag = true;

    g_pClient->Run();

    bResult = true;
Exit0:
    if (bInitFlag)
    {
        g_pClient->UnInit();
        bInitFlag = false;
    }

    if (g_pClient)
    {
        delete g_pClient;
        g_pClient = NULL;
    }

    return 0;
}
