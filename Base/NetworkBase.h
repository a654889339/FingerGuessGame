#ifndef _NETWORK_BASE_H_
#define _NETWORK_BASE_H_

#define MAX_RECV_BUFFER_SIZE 65536







static DWORD _dwNetwork_Init_Count = 0;

static bool InitNetwork()
{
    bool bResult = false;

    if (_dwNetwork_Init_Count == 0)
    {
#ifdef _WIN32
        WORD sockVersion = MAKEWORD(2, 2);
        WSADATA wsaData;
        JYLOG_PROCESS_ERROR(WSAStartup(sockVersion, &wsaData) == 0);
#endif
    }

    _dwNetwork_Init_Count++;

    bResult = true;
Exit0:
    return bResult;
}

static bool UnInitNetwork()
{
    bool bResult = false;

    _dwNetwork_Init_Count--;

    if (_dwNetwork_Init_Count == 0)
    {
#ifdef _WIN32
        WSACleanup();
#endif
    }

    bResult = true;
Exit0:
    return bResult;
}

#endif