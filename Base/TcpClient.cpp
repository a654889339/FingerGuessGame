 #include "stdafx.h"
#include "TcpClient.h"

#ifdef _CLIENT
TcpClient::TcpClient()
{
    m_bRunFlag = false;
    m_Socket = INVALID_SOCKET;
    _InitNetwork();

    memset(m_szRecvBuffer, 0, sizeof(m_szRecvBuffer));
}

TcpClient::~TcpClient()
{
    Quit();
    _UnInitNetwork();
}

bool TcpClient::Connect(const char szIP[], int nPort)
{
    bool bResult = false;
    int  nRetCode = 0;
    bool bSocketInitFlag = false;
    sockaddr_in serAddr;

    JYLOG_PROCESS_ERROR(szIP);
    JYLOG_PROCESS_ERROR(!m_bRunFlag);

    m_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    JYLOG_PROCESS_ERROR(m_Socket != INVALID_SOCKET);
    bSocketInitFlag = true;

    serAddr.sin_family = AF_INET;
    serAddr.sin_port = htons(nPort);
    serAddr.sin_addr.S_un.S_addr = inet_addr(szIP);

    nRetCode = connect(m_Socket, (sockaddr*)&serAddr, sizeof(serAddr));
    JYLOG_PROCESS_ERROR(nRetCode != SOCKET_ERROR);

    m_bRunFlag = true;

    bResult = true;
Exit0:
    if (!bResult)
    {
        if (bSocketInitFlag)
        {
            bSocketInitFlag = false;
            closesocket(m_Socket);
        }
    }
    return bResult;
}

void TcpClient::ProcessNetwork()
{
    bool bResult = false;
    bool bRetCode = false;
    int nRetCode = 0;

    JY_PROCESS_SUCCESS(!m_bRunFlag);

    nRetCode = _CanRecv(m_Socket);
    JY_PROCESS_SUCCESS(nRetCode == 0);
    if (nRetCode < 0)
    {
        nRetCode = _SocketCanRestore();
        JY_PROCESS_SUCCESS(nRetCode);

        goto Exit0;
    }

    nRetCode = recv(m_Socket, m_szRecvBuffer, min(m_RecvFD.RecvQueue.res_size(), sizeof(m_szRecvBuffer)), 0);
    JY_PROCESS_SUCCESS(nRetCode == 0);

    if (nRetCode < 0)
    {
        nRetCode = _SocketCanRestore();
        JY_PROCESS_SUCCESS(nRetCode);

        goto Exit0;
    }

    bRetCode = m_RecvFD.RecvQueue.push(m_szRecvBuffer, nRetCode);
    JYLOG_PROCESS_ERROR(bRetCode);

    bRetCode = _TCPGetFullPackage(&m_RecvFD, m_szRecvBuffer);
    JY_PROCESS_SUCCESS(!bRetCode);

    ProcessPackage((byte*)m_szRecvBuffer, m_RecvFD.uProtoSize);

Exit1:
    bResult = true;
Exit0:
    if (!bResult)
    {
        Quit();
        ConnectionLost();
    }
    return;
}

bool TcpClient::Send(void* pbyData, size_t uDataLen)
{
    bool bResult = false;
    bool bRetCode = false;

    JY_PROCESS_SUCCESS(!m_bRunFlag);
    JYLOG_PROCESS_ERROR(pbyData);

    // Async + encrypt + Compress
    JYLOG_PROCESS_ERROR(uDataLen + 2 < sizeof(m_szSendBuffer));

    *(WORD*)m_szSendBuffer = (WORD)uDataLen;
    memcpy(m_szSendBuffer + 2, pbyData, uDataLen);

    bRetCode = _TCPSend(m_Socket, m_szSendBuffer, uDataLen + 2);
    JYLOG_PROCESS_ERROR(bRetCode);

Exit1:
    bResult = true;
Exit0:
    if (!bResult)
    {
        Quit();
        ConnectionLost();
    }
    return bResult;
}

bool TcpClient::IsEnable()
{
    return m_bRunFlag;
}

void TcpClient::Quit()
{
    if (m_bRunFlag)
    {
        m_bRunFlag = false;
        closesocket(m_Socket);
    }
}

#endif