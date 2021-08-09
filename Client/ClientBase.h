#ifndef _CLIENT_BASE_H_
#define _CLIENT_BASE_H_

#include "stdafx.h"

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
    "��ʼ��ս�����ȭ:\n"
    "����:Scissors\n"
    "ʯͷ:Rock\n"
    "��:Paper",
};


static bool CheckNickName(const char szName[])
{
    bool bResult = false;

    for (int i = 0; i < _NAME_LEN && szName[i]; i++)
    {
        if (i != 0)
            JY_TRUE_CONTINUE(szName[i] >= '0' && szName[i] <= '9');

        JY_TRUE_CONTINUE(szName[i] >= 'A' && szName[i] <= 'Z');
        JY_PROCESS_ERROR(szName[i] >= 'a' && szName[i] <= 'z');
    }

    JY_STD_BOOL_END
}

#endif