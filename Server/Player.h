#ifndef _PLAYER_H_
#define _PLAYER_H_


class Player
{
public:
    Player();
    virtual ~Player();

    bool Init(DWORD dwPlayerID, int nConnIndex, const char szName[]);
    void UnInit();

public:
    DWORD m_dwPlayerID;
    int m_nConnIndex;
    char m_szName[_NAME_LEN];
    GameState m_eState;
};

#endif