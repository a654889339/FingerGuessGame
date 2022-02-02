#ifndef _BASE_ACCOUNT_SERVER_GAME_CENTER_PROTOCOL_H_
#define _BASE_ACCOUNT_SERVER_GAME_CENTER_PROTOCOL_H_

#include "ProtocolBase.h"
#include "RouterModuleBase.h"

enum ACCOUNT_GAMECENTER_PROTOCOL_ID
{
    eas2gc_begin = 0,

    eas2gc_player_login_request,

    eas2gc_end
};

enum GAMECENTER_ACCOUNT_PROTOCOL_ID
{
    egc2as_begin = 0,

    egc2as_player_login_respond,

    egc2as_end
};

// Account Server --> GameCenter
struct AS2GC_PLAYER_LOGIN_REQUEST
{
    uint64_t uOpenId;
};

// GameCenter --> Account Server
struct GC2AS_PLAYER_LOGIN_RESPOND
{
    uint64_t uOpenId;
};

#endif