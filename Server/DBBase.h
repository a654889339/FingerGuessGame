#ifndef _DB_BASE_H_
#define _DB_BASE_H_

#include "mysql.h"
#include "mysqld_error.h"

MYSQL* MySQL_Connect(const char cszDBAddr[], const char cszDBName[], const char cszUserName[], const char cszPassword[], int nPort);
void MySQL_Disconnect(MYSQL* pHandle);
BOOL MySQL_Query(MYSQL* pHandle, const char cszSQL[], unsigned* puRetMySQLErrorCode = NULL, bool bSilentMode = false);
BOOL MYSQL_CheckError(MYSQL* pHandle);
#endif