#include "stdafx.h"
#include "ServerConnection.h"

ServerConnection::ServerConnection()
{

}

ServerConnection::~ServerConnection()
{

}

bool ServerConnection::Init(const char szIP[], int nPort)
{
    bool bResult = false;
    bool bRetCode = false;

    bRetCode = Bind(szIP, nPort);
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_BOOL_END
}

void ServerConnection::UnInit()
{

}

void ServerConnection::Active()
{

}