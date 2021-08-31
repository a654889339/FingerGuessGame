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
    JYLOG_PROCESS_ERROR(nPort);


    bResult = true;
Exit0:
    return bResult;
}