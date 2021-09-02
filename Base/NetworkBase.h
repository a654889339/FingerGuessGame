#ifndef _NETWORK_BASE_H_
#define _NETWORK_BASE_H_

#include "stdafx.h"

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

    int nRetCode = select(Socket + 1, NULL, &FDSet, NULL, &timeout);

    if (nRetCode == 0)
        return 0;

    if (nRetCode > 0)
        return 1;

    return -1;
}

static bool _Send(SOCKET Socket, void* pbyData, size_t uDataLen)
{
    bool bResult = false;
    int nRetCode = 0;
    char* pOffset = (char*)pbyData;

    JYLOG_PROCESS_ERROR(pbyData);

    while (uDataLen > 0)
    {
        nRetCode = _CanSend(Socket);
        JYLOG_PROCESS_ERROR(nRetCode != 0);
        if (nRetCode < 0)
        {
            JY_TRUE_CONTINUE(_SocketCanRestore());
            goto Exit0;
        }

        nRetCode = send(Socket, pOffset, uDataLen, 0);
        JYLOG_PROCESS_ERROR(nRetCode != 0);

        if (nRetCode < 0)
        {
            JY_TRUE_CONTINUE(_SocketCanRestore());
            goto Exit0;
        }

        pOffset += nRetCode;
        uDataLen -= nRetCode;
    }

    bResult = true;
Exit0:
    return bResult;
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

    int nRetCode = select(Socket + 1, &FDSet, NULL, NULL, &timeout);

    if (nRetCode == 0)
        return 0;

    if (nRetCode > 0)
        return 1;

    return -1;
}

// Process recv buffer
typedef CycleQueue<char> RECV_QUEUE;
struct RecvFD
{
    SOCKET Socket;
    int nConnIndex;
    bool bHaveProtoSize;
    size_t uProtoSize;
    time_t nActiveTime;
    bool bConnFlag;
    RECV_QUEUE RecvQueue;

    RecvFD()
    {
        Clear();
        RecvQueue.init(MAX_RECV_BUFFER_SIZE);
    }

    void Clear()
    {
        Socket = INVALID_SOCKET;
        nConnIndex = INVALID_CONNINDEX;
        bHaveProtoSize = false;
        uProtoSize = 0;
        nActiveTime = 0;
        bConnFlag = false;
        RecvQueue.clear();
    }

    void Connect(SOCKET _Socket, int _nConnIndex)
    {
        Clear();
        Socket = _Socket;
        nConnIndex = _nConnIndex;
        nActiveTime = time(NULL);
        bConnFlag = true;
    }
};

struct KCPRecvFD
{
	int nConnIndex;
	bool bHaveProtoSize;
	size_t uProtoSize;
	time_t nActiveTime;
	bool bConnFlag;
	RECV_QUEUE RecvQueue;

    KCPRecvFD()
	{
		Clear();
		RecvQueue.init(MAX_RECV_BUFFER_SIZE);
	}

	void Clear()
	{
		nConnIndex = INVALID_CONNINDEX;
		bHaveProtoSize = false;
		uProtoSize = 0;
		nActiveTime = 0;
		bConnFlag = false;
		RecvQueue.clear();
	}

	void Connect(int _nConnIndex)
	{
		Clear();
		nConnIndex = _nConnIndex;
		nActiveTime = time(NULL);
		bConnFlag = true;
	}
};


static bool _GetFullPackage(RecvFD* pRecvFD, char* pszRecvBuffer)
{
    bool bResult = false;
    bool bRetCode = false;

    JYLOG_PROCESS_ERROR(pRecvFD);
    JYLOG_PROCESS_ERROR(pszRecvBuffer);

    if (!pRecvFD->bHaveProtoSize)
    {
        JY_PROCESS_ERROR(pRecvFD->RecvQueue.size() >= 2);
        pRecvFD->bHaveProtoSize = true;

        bRetCode = pRecvFD->RecvQueue.pop(2, pszRecvBuffer);
        JYLOG_PROCESS_ERROR(bRetCode);

        pRecvFD->uProtoSize = *(WORD*)pszRecvBuffer;
    }

    JY_PROCESS_ERROR(pRecvFD->bHaveProtoSize);
    JY_PROCESS_ERROR(pRecvFD->RecvQueue.size() >= pRecvFD->uProtoSize);

    bRetCode = pRecvFD->RecvQueue.pop(pRecvFD->uProtoSize, pszRecvBuffer);
    JYLOG_PROCESS_ERROR(bRetCode);

    pRecvFD->bHaveProtoSize = false;

    bResult = true;
Exit0:
    return bResult;
}

#endif