#ifndef _NETWORK_BASE_H_
#define _NETWORK_BASE_H_

#include "stdafx.h"
#include<ctime>

#define MAX_ACCEPT_CONNECTION 105
#define MAX_RECV_BUFFER_SIZE 65536
#define INVALID_CONNINDEX - 1
#define CONNECTION_TIME_OUT 60
// Network
static DWORD _dwNetwork_Init_Count = 0;

static bool _InitNetwork()
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

static void _UnInitNetwork()
{
    _dwNetwork_Init_Count--;

    if (_dwNetwork_Init_Count == 0)
    {
#ifdef _WIN32
        WSACleanup();
#endif
    }
}
// Process recv buffer
typedef CycleQueue<char> RECV_QUEUE;

static inline int _SocketCanRestore()
{
    return (WSAGetLastError() == EINTR);
}

// Send
// return -1: error, 0: timeout, 1: success
static inline int _CanSend(SOCKET Socket)
{
    fd_set FDSet;
    timeval timeout{ 0, 0 };

    if (Socket < 0)
        return -1;

    FD_ZERO(&FDSet);
    FD_SET(Socket, &FDSet);

    int nRetCode = select((int)Socket + 1, NULL, &FDSet, NULL, &timeout);

    if (nRetCode == 0)
        return 0;

    if (nRetCode > 0)
        return 1;

    return -1;
}

// Recv
// return -1: error, 0: timeout, 1: success
static inline int _CanRecv(SOCKET Socket)
{
    fd_set FDSet;
    timeval timeout{ 0, 0 };

    if (Socket < 0)
        return -1;

    FD_ZERO(&FDSet);
    FD_SET(Socket, &FDSet);

    int nRetCode = select((int)Socket + 1, &FDSet, NULL, NULL, &timeout);

    if (nRetCode == 0)
        return 0;

    if (nRetCode > 0)
        return 1;

    return -1;
}

#endif