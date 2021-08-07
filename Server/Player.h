#ifndef _PLAYER_H_
#define _PLAYER_H_

class Player
{
public:
    Player();
    virtual ~Player();

    bool Init(int nConnIndex, const char szName[]);
    void UnInit();

public:
    int m_nConnIndex;

private:
    char m_szName[_NAME_LEN];
};

#endif