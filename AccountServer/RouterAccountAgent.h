#ifndef _ACCOUNT_ROUTER_AGENT_H_
#define _ACCOUNT_ROUTER_AGENT_H_

#include "RouterModuleAgent.h"
#include "ACCOUNT_SERVER_GAME_CENTER_PROTOCOL.h"

class RouterAccountAgent
{
public:
    RouterAccountAgent();
    virtual ~RouterAccountAgent();

    bool Init();
    void UnInit();

    void Active();

    bool DoAS2GCPlayerLoginRequest(uint64_t uOpenId);

private:
    void OnGC2ASPlayerLoginRespond(BYTE* pbyData, size_t uSize);

    ROUTER_AGENT_DEFINE(RouterAccountAgent)
};

#endif