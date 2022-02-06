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
    void ProcessNetwork();

private:
    typedef void (RouterGameCenterAgent::* PROCESS_PROTOCOL_FUNC)(BYTE* pbyData, size_t uSize);
    typedef std::vector<PROCESS_PROTOCOL_FUNC> RouterProtocolFuncVector;

    RouterProtocolFuncVector m_ProcessProtocolFuns[ermt_end];
    RouterProtocolSizeVector m_ProcessProtocolSize[ermt_end];
    BYTE                     m_byRecvBuffer[MAX_INTERNAL_NETWORK_PROTOCOL_SIZE];

    RouterModuleAgent       m_Agent;
};

#endif