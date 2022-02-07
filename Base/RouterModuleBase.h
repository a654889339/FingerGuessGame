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