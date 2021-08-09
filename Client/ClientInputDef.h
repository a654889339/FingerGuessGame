#ifndef _CLIENT_INPUT_DEF_H_
#define _CLIENT_INPUT_DEF_H_

#include "stdafx.h"

#define MAX_INPUT_BUFFER_SIZE 1024

enum CLIENT_INPUT_PROTOCOL_CODE
{
    cipc_invalid = 0,

    cipc_show,
    cipc_create,
    cipc_join,
    cipc_join_input_name,
    cipc_game_rock,
    cipc_game_scissors,
    cipc_game_paper,

    cipc_quit,

    cipc_total,
};

const char _szInputProtocolName[cipc_total][_NAME_LEN] = 
{
    "INVALID",
    "Show",
    "Create",
    "Join",
    "",
    "Rock",
    "Scissors",
    "Paper",

    "Quit",
};

#endif