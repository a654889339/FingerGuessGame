#ifndef _GAMEPLAYER_PLAYER_CONFIG_H_
#define _GAMEPLAYER_PLAYER_CONFIG_H_

enum GameState
{
    egame_state_begin = 0,
    egame_state_login,
    egame_state_idle,
    egame_state_waiting,
    egame_state_playing,

    egame_state_end,
};

const char szGameState[egame_state_end][_NAME_LEN] =
{
    "失效",
    "登录中",
    "空闲",
    "等待加入",
    "正在游戏",
};


#endif