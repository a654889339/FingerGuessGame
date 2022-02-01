#ifndef _ROUTER_MODULE_MGR_H_
#define _ROUTER_MODULE_MGR_H_

#include "RouterModule.h"

class RouterModuleMgr
{
public:
    RouterModuleMgr();
    virtual ~RouterModuleMgr();

    bool Init();
    void UnInit();

    void Run();

private:
    void ProcessModule(RouterModule* pModule);

    RouterModule* GetModule(RouterModuleType eType);

private:
    RouterModule m_szModule[ermt_end];
    BYTE         m_byTempBuffer[MAX_INTERNAL_NETWORK_PROTOCOL_SIZE];
};

#endif