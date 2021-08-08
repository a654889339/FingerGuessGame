#ifndef _CLIENT_INPUT_DEF_H_
#define _CLIENT_INPUT_DEF_H_

#define MAX_INPUT_BUFFER_SIZE 10

enum CLIENT_INPUT_PROTOCOL_CODE
{
    cipc_invalid = 0,

    cipc_quit,

    cipc_total,
};

const char _szInputProtocolName[cipc_total][_NAME_LEN] = 
{
    "INVALID",
    "Quit",
};

#endif