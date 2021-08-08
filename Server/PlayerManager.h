#ifndef _PLAYER_MANAGER_H_
#define _PLAYER_MANAGER_H_

#include "Player.h"

class PlayerManager
{
public:
    PlayerManager();
    virtual ~PlayerManager();

    bool Init();
    void UnInit();

    bool AddPlayer(int nConnIndex, const char szName[]);
    void RemovePlayer(int nConnIndex);

    bool IsOnline(const char szName[]);

private:
    DWORD LoadPlayerFromDB(const char szName[]);

private:
    typedef SplayTree<DWORD, Player> PLAYER_MANAGER_MAP;
    PLAYER_MANAGER_MAP m_PlayerManager;

    typedef SplayTree<STString, DWORD> PLAYER_NAME_MANAGER;
    PLAYER_NAME_MANAGER m_NameManager;

    typedef SplayTree<int, DWORD> PLAYER_CONNINDEX_MAP;
    PLAYER_CONNINDEX_MAP m_ConnIndexManager;

};

#endif