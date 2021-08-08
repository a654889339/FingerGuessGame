#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

#define PING_TIME_INTERVAL 1
#define UNDEFINED_PROTOCOL_SIZE -1

enum CLIENT_SERVER_PROTOCOL_CODE
{
    c2s_begin,

    c2s_ping_request,
    c2s_login_request,

    c2s_end
};

enum SERVER_CLIENT_PROTOCOL_CODE
{
    s2c_begin,

    s2c_ping_respond,
    s2c_login_respond,

    s2c_end
};

enum PROTOCOL_ERROR_CODE
{
    pec_invalid = 0,

    pec_login_succeed,
    pec_login_already_exist,


};

#pragma pack(1)

struct PROTOCOL_HEADER
{
    WORD wProtocolID;
};

//////////////////////////////////////////////////////////////////////////
struct C2S_PING_REQUEST : PROTOCOL_HEADER
{
};

struct C2S_LOGIN_REQUEST : PROTOCOL_HEADER
{
    char szName[_NAME_LEN];
};

//////////////////////////////////////////////////////////////////////////
struct S2C_PING_RESPOND : PROTOCOL_HEADER
{
};

struct S2C_LOGIN_RESPOND : PROTOCOL_HEADER
{
    int nRetCode;
};

#pragma pack()

#endif