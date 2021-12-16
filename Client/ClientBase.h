#ifndef _CLIENT_BASE_H_
#define _CLIENT_BASE_H_

#include "stdafx.h"

static bool CheckNickName(const char szName[])
{
    bool bResult = false;

    for (int i = 0; i < _NAME_LEN && szName[i]; i++)
    {
        if (i != 0)
            JY_TRUE_CONTINUE(szName[i] >= '0' && szName[i] <= '9');

        JY_TRUE_CONTINUE(szName[i] >= 'A' && szName[i] <= 'Z');
        JY_PROCESS_ERROR(szName[i] >= 'a' && szName[i] <= 'z');
    }

    JY_STD_BOOL_END
}

#endif