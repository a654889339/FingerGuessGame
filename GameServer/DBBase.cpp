#include "stdafx.h"
#include "DBBase.h"
//
//static const unsigned long MYSQL5_VERSION_ID = 50000; // MySQL 5 Version ID
//
//MYSQL* MySQL_Connect(const char cszDBAddr[], const char cszDBName[], const char cszUserName[], const char cszPassword[], int nPort)
//{
//    MYSQL* pResult = NULL;
//    int           nRetCode = false;
//    MYSQL* pDBHandle = NULL;
//    MYSQL* pTmpHandle = NULL;
//    my_bool       bReconnectFlag = 0;
//    unsigned long ulMySQLClientVersionID = 0;
//    int           nStrLen = 0;
//    char          szSQL[1024];
//
//    pDBHandle = mysql_init(NULL);
//    JY_PROCESS_ERROR(pDBHandle);
//
//    // enable reconnect if MySQL client version > 5
//    ulMySQLClientVersionID = mysql_get_client_version();
//    if (ulMySQLClientVersionID >= MYSQL5_VERSION_ID)
//    {
//        bReconnectFlag = 1;
//        nRetCode = mysql_options(pDBHandle, MYSQL_OPT_RECONNECT, &bReconnectFlag);
//        JY_PROCESS_ERROR(nRetCode == 0);
//    }
//
//    pTmpHandle = mysql_real_connect(
//        pDBHandle, cszDBAddr, cszUserName, cszPassword, "", nPort, NULL, 0
//    );
//    if (pTmpHandle == NULL)
//    {
//        printf(
//            "[DB] Can't open database \"%s\" at \"%s\", db error : \"%s\"\n",
//            cszDBName, cszDBAddr, mysql_error(pDBHandle)
//        );
//        goto Exit0;
//    }
//
//    nStrLen = snprintf(
//        szSQL, sizeof(szSQL), "create database if not exists %s", cszDBName
//    );
//    JY_PROCESS_ERROR(nStrLen > 0 && nStrLen < (int)sizeof(szSQL));
//
//    nRetCode = MySQL_Query(pDBHandle, szSQL);
//    JY_PROCESS_ERROR(nRetCode);
//
//    nRetCode = mysql_select_db(pDBHandle, cszDBName);
//    JY_PROCESS_ERROR(nRetCode == 0);
//
//    pResult = pDBHandle;
//Exit0:
//    if (!pResult)
//    {
//        if (pDBHandle)
//        {
//            printf("%d:%s\n", mysql_errno(pDBHandle), mysql_error(pDBHandle));
//
//            mysql_close(pDBHandle);
//            pDBHandle = NULL;
//        }
//    }
//    return pResult;
//}
//
//void MySQL_Disconnect(MYSQL* pHandle)
//{
//    if (pHandle)
//    {
//        mysql_close(pHandle);
//        pHandle = NULL;
//    }
//}
//
//#define CR_SERVER_LOST      2013
//#define CR_CONN_HOST_ERROR  2003
//#define CR_SERVER_GONE_ERROR    2006
//
//bool MySQL_Query(MYSQL* pHandle, const char cszSQL[], unsigned* puRetMySQLErrorCode /*= NULL*/, bool bSilentMode /*= false*/)
//{
//    bool        bResult = false;
//    int         nRetCode = false;
//    int         nReconnectTimes = 0;
//    unsigned    uMySQLErrorCode = 0;
//    size_t      uStrLen = strlen(cszSQL);
//
//    assert(pHandle);
//    assert(cszSQL);
//
//    while (true)
//    {
//        uMySQLErrorCode = 0;
//        nRetCode = mysql_real_query(pHandle, cszSQL, (unsigned long)uStrLen);
//        if (nRetCode == 0)
//            break;
//
//        uMySQLErrorCode = mysql_errno(pHandle);
//        JY_PROCESS_ERROR(uMySQLErrorCode != ER_DUP_ENTRY);
//
//        if (
//            (uMySQLErrorCode != CR_SERVER_LOST) &&
//            (uMySQLErrorCode != CR_CONN_HOST_ERROR) &&
//            (uMySQLErrorCode != CR_SERVER_GONE_ERROR)
//            )
//        {
//            if (!bSilentMode)
//            {
//                printf(
//                    "[DB] Call \"mysql_real_query\" failed : %s\n",
//                    mysql_error(pHandle)
//                );
//            }
//
//            goto Exit0;
//        }
//
//        while (nReconnectTimes < 5)
//        {
//            nRetCode = mysql_ping(pHandle);
//            if (nRetCode == 0)
//                break;
//
//            Sleep(300);
//            ++nReconnectTimes;
//        }
//
//        if (nReconnectTimes >= 5)
//        {
//            if (!bSilentMode)
//            {
//                printf(
//                    "[DB] Call \"mysql_ping\" failed : %s\n",
//                    mysql_error(pHandle)
//                );
//            }
//
//            goto Exit0;
//        }
//    }
//
//    bResult = true;
//Exit0:
//    if (puRetMySQLErrorCode)
//    {
//        *puRetMySQLErrorCode = uMySQLErrorCode;
//    }
//    return bResult;
//}
//
//bool MYSQL_CheckError(MYSQL* pHandle)
//{
//    bool        bResult = false;
//    unsigned    uMySQLErrorCode = 0;
//
//    assert(pHandle);
//
//    uMySQLErrorCode = mysql_errno(pHandle);
//    if (uMySQLErrorCode != 0)
//    {
//        printf(
//            "[DB] failed, ERROR_ID(%u) : %s\n", uMySQLErrorCode, mysql_error(pHandle)
//        );
//        goto Exit0;
//    }
//
//    bResult = true;
//Exit0:
//    return bResult;
//}