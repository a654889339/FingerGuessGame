#ifndef _GLOBAL_DEF_H_
#define _GLOBAL_DEF_H_

#define _NAME_LEN 32
#define ERROR_ID 0

enum GameState
{
    egame_state_begin = 0,
    egame_state_login = egame_state_begin,
    egame_state_idle,
    egame_state_waiting,
    egame_state_playing,

    egame_state_end,
};

class Player;

class PLAYER_STATE_TRIGGER
{
public:
    virtual void Enter(GameState eState, Player* pPlayer) {};
    virtual void Leave(GameState eState, Player* pPlayer) {};
};

class PLAYER_STATE_MANAGER
{
public:
    PLAYER_STATE_MANAGER()
    {
        for (int i = egame_state_login; i < egame_state_end; i++)
        {
            m_PlayerState[i] = &m_PlayerStateConst[i];
        }
    }

public:
    PLAYER_STATE_TRIGGER* m_PlayerState[egame_state_end];

private:
    PLAYER_STATE_TRIGGER m_PlayerStateConst[egame_state_end];
};
#endif