#ifndef _BASE_CLIENT_ACCOUNT_SERVER_PROTOCOL_H_
#define _BASE_CLIENT_ACCOUNT_SERVER_PROTOCOL_H_

#include "stdafx.h"
#include "ProtocolBase.h"
#include "AccountDef.h"

#define CLIENT_ACCOUNT_SERVER_LISTEN_IP   "127.0.0.1"
#define CLIENT_ACCOUNT_SERVER_LISTEN_PORT 11451

#define ACCOUNT_SERVER_VERSION 0

enum CLIENT_ACCOUNT_SERVER_PROTOCOL_ID
{
    ec2as_being = 0,

    ec2as_login_request,

    ec2as_end
};

enum ACCOUNT_SERVER_CLIENT_PROTOCOL_ID
{
    eas2c_being = 0,

    eas2c_login_respond,

    eas2c_end
};

//////////////////////////////////////////////////////////////////////////

struct C2AS_LOGIN_REQUEST
{
    int  nAccountServerVersion;
    char szAccountName[MAX_ACCOUNT_NAME_LEN];
    char szPassword[MAX_ACCOUNT_PASSWORD_LEN];
};

//////////////////////////////////////////////////////////////////////////

struct AS2C_LOGIN_RESPOND
{
    uint32 uGateIP;
    int    nGatePort;
    uint32 uMapID;
    int32  nMapIndex;
    int    nX;
    int    nY;
    int    nZ;
};

#endif