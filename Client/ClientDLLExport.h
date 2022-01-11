#ifndef CLIENT_DLL_EXPORT_H_
#define CLIENT_DLL_EXPORT_H_

#include "ClientLogic.h"

class _declspec(dllexport) ClientDLLExport
{
public:
    ClientDLLExport()
    {
        g_pClient = NULL;
        assert(!g_pClient);
    }

    ~ClientDLLExport()
    {
        assert(!g_pClient);
    }

    bool Init()
    {
        bool bResult = false;

        JYLOG_PROCESS_ERROR(!g_pClient);

        g_pClient = new ClientLogic();
        JYLOG_PROCESS_ERROR(g_pClient);

        JY_STD_BOOL_END
    }

    void UnInit()
    {
        assert(g_pClient);

        delete g_pClient;
    }
};

#endif