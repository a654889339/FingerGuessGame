#ifndef _NETWORK_BASE_H_
#define _NETWORK_BASE_H_

#include "MySTL.h"

#define MAX_ACCEPT_CONNECTION 105
#define MAX_RECV_BUFFER_SIZE 65536

// Network
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

static inline int SocketCanRestore()
{
    return (WSAGetLastError() == EINTR);
}

// Send
// return -1: error, 0: timeout, 1: success
static inline int CanSend(int nSocket, const timeval* pTimeout)
{
    fd_set FDSet;
    timeval TempTimeout;
    timeval* pTempTimeout = NULL;

    if (nSocket < 0)
        return -1;

    FD_ZERO(&FDSet);
    FD_SET(nSocket, &FDSet);

    if (pTimeout)
    {
        TempTimeout = *pTimeout;
        pTempTimeout = &TempTimeout;
    }

    int nRetCode = select(nSocket + 1, NULL, &FDSet, NULL, pTempTimeout);

    if (nRetCode == 0)
        return 0;

    if (nRetCode > 0)
        return 1;

    return -1;
}

// Recv
// return -1: error, 0: timeout, 1: success
static inline int CanRecv(int nSocket, const timeval* pTimeout)
{
    fd_set FDSet;
    timeval TempTimeout;
    timeval* pTempTimeout = NULL;

    if (nSocket < 0)
        return -1;

    FD_ZERO(&FDSet);
    FD_SET(nSocket, &FDSet);

    if (pTimeout)
    {
        TempTimeout = *pTimeout;
        pTempTimeout = &TempTimeout;
    }

    int nRetCode = select(nSocket + 1, &FDSet, NULL, NULL, pTempTimeout);

    if (nRetCode == 0)
        return 0;

    if (nRetCode > 0)
        return 1;

    return -1;
}

// Process recv buffer
typedef CycleQueue<char, MAX_RECV_BUFFER_SIZE> RECV_QUEUE;
struct RecvFD
{
    bool bHaveProtoSize;
    size_t uProtoSize;
    bool bConnFlag;
    RECV_QUEUE RecvQueue;

    RecvFD()
    {
        Clear();
    }

    void Clear()
    {
        bHaveProtoSize = false;
        uProtoSize = 0;
        bConnFlag = false;
        RecvQueue.clear();
    }
};

static bool GetFullPackage(RecvFD* pRecvFD, char* pszRecvBuffer)
{
    bool bResult = false;
    bool bRetCode = false;

    JYLOG_PROCESS_ERROR(pRecvFD);
    JYLOG_PROCESS_ERROR(pszRecvBuffer);

    if (pRecvFD->bHaveProtoSize)
    {
        JY_PROCESS_ERROR(pRecvFD->RecvQueue.size() >= pRecvFD->uProtoSize);

        bRetCode = pRecvFD->RecvQueue.pop(pRecvFD->uProtoSize, pszRecvBuffer);
        JYLOG_PROCESS_ERROR(bRetCode);

        pRecvFD->bHaveProtoSize = false;
    }
    else
    {
        JY_PROCESS_ERROR(pRecvFD->RecvQueue.size() >= 2);
        pRecvFD->bHaveProtoSize = true;

        bRetCode = pRecvFD->RecvQueue.pop(2, pszRecvBuffer);
        JYLOG_PROCESS_ERROR(bRetCode);

        pRecvFD->uProtoSize = pszRecvBuffer[0] << 8 | pszRecvBuffer[1];
    }

    bResult = true;
Exit0:
    return bResult;
}

#endif