#ifndef _CLIENT_GAME_ENGINE_PROTOCOL_H_
#define _CLIENT_GAME_ENGINE_PROTOCOL_H_

struct CLIENT_GAME_ENGINE_PROTOCOL_HEADER
{
    WORD wProtocolID;
};

enum CLIENT_GAME_ENGINE_PROTOCOL_ID
{
    ec2ge_begin = 0,

    ec2ge_login_request,

    ec2ge_end
};

enum GAME_ENGINE_CLIENT_PROTOCOL_ID
{
    ege2c_begin = 0,

    ege2c_login_respond,

    ege2c_end
};

//////////////////////////////////////////////////////////////////////////

struct GE2C_LOGIN_REQUEST: CLIENT_GAME_ENGINE_PROTOCOL_HEADER
{
    int nTestNum;
};

//////////////////////////////////////////////////////////////////////////

struct C2GE_LOGIN_RESPOND: CLIENT_GAME_ENGINE_PROTOCOL_HEADER
{


};


#endif