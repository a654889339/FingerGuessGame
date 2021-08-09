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
    "查看在线用户列表:Show\n"
    "开设战局:Create\n"
    "加入战局:Join\n"
    "退出游戏:Quit",

    // egame_state_waiting
    "等待其他人加入",

    // egame_state_playing
    "开始对战，请出拳:\n"
    "剪刀:Scissors\n"
    "石头:Rock\n"
    "布:Paper",
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