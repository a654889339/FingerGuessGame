#ifndef _TCP_BASE_H_
#define _TCP_BASE_H_
#include "NetworkBase.h"
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

static bool _TCPSend(SOCKET Socket, void* pbyData, size_t uDataLen)
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

        nRetCode = send(Socket, pOffset, (int)uDataLen, 0);
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
static bool _TCPGetFullPackage(RecvFD* pRecvFD, char* pszRecvBuffer)
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
