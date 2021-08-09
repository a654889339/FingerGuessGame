#ifndef _PLAYER_MANAGER_H_
#define _PLAYER_MANAGER_H_

#include "Player.h"

class PLAYER_STATE_WAITING : public PLAYER_STATE_TRIGGER
{
public:
    void Enter(GameState eState, Player* pPlayer);
    void Leave(GameState eState, Player* pInfo);
};

class PLAYER_STATE_PLAYING : public PLAYER_STATE_TRIGGER
{
public:
    void Enter(GameState eState, Player* pPlayer);
    void Leave(GameState eState, Player* pInfo);
};

class PlayerManager : public PLAYER_STATE_MANAGER
{
public:
    PlayerManager();
    virtual ~PlayerManager();

    bool Init();
    void UnInit();

    // Add or Remove
    bool AddPlayer(int nConnIndex, const char szName[]);
    void RemovePlayer(int nConnIndex);

    // Modify
    bool SetState(int nConnIndex, GameState eState);
    bool JoinGame(int nConnIndex, Player* pHost);
    bool TryEndGame(int nConnIndex);

    // Query
    bool IsOnline(const char szName[]);

    Player* GetPlayer(DWORD dwPlayerID);
    Player* GetPlayer(int nConnIndex);
    Player* GetPlayer(const char szName[]);

public:
    typedef SplayTree<DWORD, Player> PLAYER_MANAGER_MAP;
    PLAYER_MANAGER_MAP m_PlayerMap;

private:
    typedef SplayTree<STString, DWORD> PLAYER_NAME_MANAGER;
    PLAYER_NAME_MANAGER m_NameManager;

    typedef SplayTree<int, DWORD> PLAYER_CONNINDEX_MAP;
    PLAYER_CONNINDEX_MAP m_ConnIndexManager;

    PLAYER_STATE_WAITING m_PlayerStateWaiting;
    PLAYER_STATE_PLAYING m_PlayerStatePlaying;
};

#endif