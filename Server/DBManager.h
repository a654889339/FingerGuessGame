#ifndef _DB_MANAGER_H_
#define _DB_MANAGER_H_

#include "DBBase.h"
#include "Player.h"

class DBManager
{
public:
    DBManager();
    virtual ~DBManager();

    bool Init();
    void UnInit();

    void Quit();
    bool IsEnable();

    DWORD LoadPlayerIDByName(const char szName[]);
    bool LoadPlayer(Player* pPlayer);

private:
    bool m_bRunFlag;
};

#endif