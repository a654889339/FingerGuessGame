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
    cipc_quit,

    cipc_total,
};

const char _szInputProtocolName[cipc_total][_NAME_LEN] = 
{
    "INVALID",
    "Show",
    "Create",
    "Join",
    "Quit",
};

const char szStateContent[egame_state_end][1024] =
{
    // egame_state_begin
    "",

    // egame_state_login
    "",

    // egame_state_idle
    "�鿴�����û��б�:Show\n"
    "����ս��:Create\n"
    "����ս��:Join\n"
    "�˳���Ϸ:Quit",

    // egame_state_waiting
    "�ȴ������˼���",

    // egame_state_playing
    "",
};

#endif