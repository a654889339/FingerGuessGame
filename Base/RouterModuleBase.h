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