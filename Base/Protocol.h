#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

#define UNDEFINED_PROTOCOL_SIZE -1

enum CLIENT_SERVER_PROTOCOL_CODE
{
    c2s_begin,

    c2s_handshake_request,

    c2s_end
};

enum SERVER_CLIENT_PROTOCOL_CODE
{
    s2c_begin,

    s2c_handshake_respond,

    s2c_end
};

struct PROTOCOL_HEADER
{
    WORD wProtocolID;
};

//////////////////////////////////////////////////////////////////////////
struct C2S_HANDSHAKE_REQUEST : PROTOCOL_HEADER
{

};

//////////////////////////////////////////////////////////////////////////
struct S2C_HANDSHAKE_RESPOND : PROTOCOL_HEADER
{

};

#endif