#include "stdafx.h"
#include "GateServer.h"

GateServer* g_pGateServer = NULL;

#ifdef WIN32
bool WINAPI ConsoleHandlerRoutine(DWORD dwCtrlType)
{
    if (g_pGateServer)
    {
        printf("Receive quit signal from console !\n");
        g_pGateServer->Quit();
    }
    return true;
}
#endif

int main(int argc, char* argv[])
{
    bool    bResult   = false;
    bool    bRetCode  = false;
    bool    bInitFlag = false;

    g_pGateServer = new GateServer();
    JYLOG_PROCESS_ERROR(g_pGateServer);

    bRetCode = g_pGateServer->Init();
    JYLOG_PROCESS_ERROR(bRetCode);
    bInitFlag = true;

    g_pGateServer->Run();

    bResult = true;
Exit0:
    if (bInitFlag)
    {
        g_pGateServer->UnInit();
        bInitFlag = false;
    }

    if (g_pGateServer)
    {
        delete g_pGateServer;
        g_pGateServer = NULL;
    }

    return 0;
}
