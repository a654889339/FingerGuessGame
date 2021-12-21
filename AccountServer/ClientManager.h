#ifndef _ACCOUNT_SERVER_CLIENT_MANAGER_H_
#define _ACCOUNT_SERVER_CLIENT_MANAGER_H_

#include "AccountServerBase.h"

class ClientManager
{
public:
    ClientManager();
    virtual ~ClientManager();

    bool Init();
    void UnInit();

    bool Add(const char szAccountName[], int nConnIndex);
    void Del(int nConnIndex);

private:
    SplayTree<ClientLoginInfo, int> m_InfoManager;
    SplayTree<int, ClientLoginInfo> m_ConnManager;
};

#endif