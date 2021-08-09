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

const char szGameState[egame_state_end][_NAME_LEN] = 
{
    "ʧЧ",
    "��¼��",
    "����",
    "�ȴ�����",
    "������Ϸ",
};

#endif