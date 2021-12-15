#ifndef _GAMEPLAYER_PLAYER_MANAGER_H_
#define _GAMEPLAYER_PLAYER_MANAGER_H_

#include "Player.h"

//class PLAYER_STATE_WAITING : public PLAYER_STATE_TRIGGER
//{
//public:
//    void Enter(GameState eState, Player* pPlayer);
//    void Leave(GameState eState, Player* pInfo);
//};
//
//class PLAYER_STATE_PLAYING : public PLAYER_STATE_TRIGGER
//{
//public:
//    void Enter(GameState eState, Player* pPlayer);
//    void Leave(GameState eState, Player* pInfo);
//};

class PlayerManager
{
public:
    PlayerManager();
    virtual ~PlayerManager();

    bool Init();
    void UnInit();

    // Add or Remove
    bool AddPlayer(int32 dwPlayerID, const char szName[]);
    void RemovePlayer(int32 dwPlayerID);

    // Modify

    // Query
    bool IsOnline(const char szName[]);

    Player* GetPlayer(int32 dwPlayerID);
    Player* GetPlayer(const char szName[]);

public:
    typedef SplayTree<int32, Player> PLAYER_MANAGER_MAP;
    PLAYER_MANAGER_MAP m_PlayerMap;

private:
    typedef SplayTree<STString, int32> PLAYER_NAME_MANAGER;
    PLAYER_NAME_MANAGER m_NameManager;
};

#endif