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
    "egame_state_begin",
    "egame_state_login",
    "egame_state_idle",
    "egame_state_waiting",
    "egame_state_playing",
};


#endif