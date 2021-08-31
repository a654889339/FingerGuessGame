#include "stdafx.h"
#include "KCPClient.h"

KCPClient::KCPClient()
{

}

KCPClient::~KCPClient()
{

}

BOOL KCPClient::Init(const char szIP[], int nPort)
{
    BOOL bResult = false;

    JYLOG_PROCESS_ERROR(szIP);



    bResult = true;
Exit0:
    return bResult;
}