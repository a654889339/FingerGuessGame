#ifndef _BASE_ROUTER_MODULE_BASE_H_
#define _BASE_ROUTER_MODULE_BASE_H_

#include <vector>
#include "ProtocolBase.h"

enum RouterModuleType
{
    ermt_begin = 0,

    ermt_gamecenter,
    ermt_account,
    ermt_db,
    ermt_chat,
    ermt_rank,

    ermt_end
};

struct RouterProtocolHeader
{
    uint16_t nProtocolID;
    BYTE     nModuleType; // In send module, it means dest; In recv module, it means origin. modified by routerserver.
    uint32_t uDataLen;
    BYTE     byData[0];
};

typedef std::vector<int> RouterProtocolSizeVector;

#define REGISTER_ROUTER_FUNC(eModuleType, ProtocolID, FuncName, ProtocolSize)  \
{ \
    while (m_ProcessProtocolFuns[eModuleType].size() <= ProtocolID) \
    { \
        m_ProcessProtocolFuns[eModuleType].push_back(NULL); \
        m_ProcessProtocolSize[eModuleType].push_back(0); \
    } \
    m_ProcessProtocolFuns[eModuleType][ProtocolID] = FuncName;                  \
    m_ProcessProtocolSize[eModuleType][ProtocolID] = ProtocolSize; \
}

// .h
#define ROUTER_AGENT_DEFINE(class_name) \
private:\
    void ProcessNetwork(); \
    typedef void (class_name::* PROCESS_PROTOCOL_FUNC)(BYTE* pbyData, size_t uSize); \
    typedef std::vector<PROCESS_PROTOCOL_FUNC> RouterProtocolFuncVector; \
    RouterProtocolFuncVector m_ProcessProtocolFuns[ermt_end]; \
    RouterProtocolSizeVector m_ProcessProtocolSize[ermt_end]; \
    BYTE                     m_byRecvBuffer[MAX_INTERNAL_NETWORK_PROTOCOL_SIZE]; \
    RouterModuleAgent       m_Agent;


// .cpp
#define ROUTER_AGENT_IMPLEMENT(class_name) \
void class_name::ProcessNetwork() \
{ \
    bool                  bRetCode    = false; \
    BYTE*                 pbyData     = NULL; \
    size_t                uDataLen    = 0; \
    RouterModuleType      eType       = ermt_begin; \
    uint16_t              nProtocolID = 0; \
    PROCESS_PROTOCOL_FUNC Func; \
 \
    while (true) \
    { \
        pbyData = m_byRecvBuffer; \
 \
        bRetCode = m_Agent.Recv(sizeof(m_byRecvBuffer), pbyData, &uDataLen, &eType, &nProtocolID); \
        JY_PROCESS_ERROR(bRetCode); \
        JYLOG_PROCESS_ERROR(nProtocolID < m_ProcessProtocolFuns[eType].size()); \
 \
        if (m_ProcessProtocolSize[eType][nProtocolID] != UNDEFINED_PROTOCOL_SIZE) \
        { \
            JYLOG_PROCESS_ERROR(m_ProcessProtocolSize[eType][nProtocolID] == uDataLen); \
        } \
 \
        Func = m_ProcessProtocolFuns[eType][nProtocolID]; \
        JYLOG_PROCESS_ERROR(Func); \
 \
        (this->*Func)(pbyData, uDataLen); \
    } \
 \
Exit0: \
    return; \
}

const char szRouterModuleIPConfig[ermt_end][MAX_IP_STRING_LEN] =
{
    "",
    "127.0.0.1",
    "127.0.0.1",
    "127.0.0.1",
    "127.0.0.1",
    "127.0.0.1",
};

const int szRouterModulePortConfig[ermt_end] =
{
    0,
    11452,
    11453,
    11454,
    11455,
    11456,
};

#endif