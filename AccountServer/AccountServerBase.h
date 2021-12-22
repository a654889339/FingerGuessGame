#ifndef _ACCOUNT_SERVER_BASE_H_
#define _ACCOUNT_SERVER_BASE_H_

#include "AccountDef.h"

struct ConnectionInfo
{
    int nIP;
    int nPort;

    ConnectionInfo(int _nIP = 0, int _nPort = 0) : nIP(_nIP), nPort(_nPort) {}
};

struct ClientLoginInfo
{
    char szAccountName[MAX_ACCOUNT_NAME_LEN];

    bool operator < (const ClientLoginInfo& _Right) const {
        return strcmp(szAccountName, _Right.szAccountName) <= 0;
    }

    bool operator == (const ClientLoginInfo& _Right) const {
        return strcmp(szAccountName, _Right.szAccountName) == 0;
    }
};

#endif