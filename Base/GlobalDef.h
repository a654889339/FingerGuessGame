#ifndef _GLOBAL_DEF_H_
#define _GLOBAL_DEF_H_

#define _NAME_LEN 32
#define ERROR_ID 0

enum GameState
{
    egame_state_begin = 0,
    egame_state_login,
    egame_state_idle,
    egame_state_waiting,
    egame_state_playing,

    egame_state_end,
};

const char szStateContent[egame_state_end][1024] = 
{
    // egame_state_begin
    "",

    // egame_state_login
    "",

    // egame_state_idle
    "1.查看在线用户列表\n"
    "2.开设战局\n"
    "3.加入战局\n"
    "4.退出游戏",

    // egame_state_waiting
    "等待其他人加入",

    // egame_state_playing
    "",
};

#endif