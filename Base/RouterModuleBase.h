#ifndef _BASE_ROUTER_MODULE_BASE_H_
#define _BASE_ROUTER_MODULE_BASE_H_

#include "ProtocolBase.h"

enum RouterModuleType
{
    ermt_begin,

    ermt_gamecenter,
    ermt_account,
    ermt_db,
    ermt_chat,
    ermt_rank,

    ermt_end
};

struct RouterProtocolHeader
{
    BYTE     nModuleType;
    int      nConnIndex;
    uint32_t uDataLen;
    BYTE     byData[0];
};

#endif