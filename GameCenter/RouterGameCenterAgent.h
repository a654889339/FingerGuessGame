#ifndef _GAME_CENTER_ROUTER_AGENT_H_
#define _GAME_CENTER_ROUTER_AGENT_H_

#include "RouterModuleAgent.h"
#include "ACCOUNT_SERVER_GAME_CENTER_PROTOCOL.h"

class RouterGameCenterAgent
{
public:
    RouterGameCenterAgent();
    virtual ~RouterGameCenterAgent();

    bool Init();
    void UnInit();

    void Active();

    bool DoGC2ASPlayerLoginRespond(uint64_t uOpenId);

private:
    void OnAS2GCPlayerLoginRequest(BYTE* pbyData, size_t uSize);

    ROUTER_AGENT_DEFINE(RouterGameCenterAgent)
};

#endif