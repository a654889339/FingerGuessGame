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
    void ProcessNetwork();

private:
    typedef void (RouterAccountAgent::* PROCESS_PROTOCOL_FUNC)(BYTE* pbyData, size_t uSize);
    typedef std::vector<PROCESS_PROTOCOL_FUNC> RouterProtocolFuncVector;

    RouterProtocolFuncVector m_ProcessProtocolFuns[ermt_end];
    RouterProtocolSizeVector m_ProcessProtocolSize[ermt_end];
    BYTE                     m_byRecvBuffer[MAX_INTERNAL_NETWORK_PROTOCOL_SIZE];

    RouterModuleAgent       m_Agent;

    int m_nTest;
};

#endif