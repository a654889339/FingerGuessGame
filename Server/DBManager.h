#ifndef _DB_MANAGER_H_
#define _DB_MANAGER_H_

#include "DBBase.h"
#include "Player.h"

#define CUSTOM_PLAYER_INFO_TABLE_NAME   "PlayerInfo"

class DBManager
{
public:
    DBManager();
    virtual ~DBManager();

    bool Init(const char cszDBAddr[], int nPort,
        const char cszUserName[], const char cszPassword[], const char cszDBName[]);
    void UnInit();

    void Quit();
    bool IsEnable();

    DWORD LoadPlayerIDByName(const char szName[]);
    bool LoadPlayer(Player* pPlayer);


private:
    bool CheckTable();
    BOOL DoQuery(const char cszSQL[], bool bSilentMode = false);

private:
    MYSQL*  m_pDBHandle;
    bool m_bRunFlag;
    char m_szSQL[1024];
};

#endif