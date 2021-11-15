#ifndef _KCP_BASE_H_
#define _KCP_BASE_H_

#include "NetworkBase.h"
struct KCPRecvFD
{
    int nConnIndex;
    sockaddr_in Addr;
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

    void Connect(sockaddr_in& Addr_in, int _nConnIndex)
    {
        Clear();
        Addr = Addr_in;
        nConnIndex = _nConnIndex;
        nActiveTime = time(NULL);
        bConnFlag = true;
    }
};
static bool _KCPSend(SOCKET Socket, KCPRecvFD* pKCP, void* pbyData, size_t uDataLen)
{
    bool bResult = false;
    int nRetCode = 0;
    char* pOffset = (char*)pbyData;

    JYLOG_PROCESS_ERROR(pbyData);

    while (uDataLen > 0)
    {
        nRetCode = sendto(Socket, pOffset, uDataLen, 0, (SOCKADDR*)&pKCP->Addr, sizeof(pKCP->Addr));
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

#endif
