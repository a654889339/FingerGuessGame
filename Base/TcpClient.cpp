#include "stdafx.h"
#include "TcpClient.h"

TcpClient::TcpClient()
{
    m_bRunFlag = false;
    m_Socket = INVALID_SOCKET;
    InitNetwork();

    memset(m_szRecvBuffer, 0, sizeof(m_szRecvBuffer));
}

TcpClient::~TcpClient()
{
    UnInitNetwork();
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

    JY_PROCESS_ERROR(m_bRunFlag);

    while (true)
    {
        int nRecvSize = recv(m_Socket, m_szRecvBuffer, min(m_RecvFD.RecvQueue.res_size(), sizeof(m_szRecvBuffer)), 0);
        if (nRecvSize > 0)
        {
            bRetCode = m_RecvFD.RecvQueue.push(m_szRecvBuffer, nRecvSize);
            JYLOG_PROCESS_ERROR(bRetCode);

            if (GetFullPackage(&m_RecvFD, m_szRecvBuffer))
            {
                ProcessPackage((byte*)m_szRecvBuffer, m_RecvFD.uProtoSize);
            }
        }
    }

    bResult = true;
Exit0:
    if (!bResult && m_bRunFlag)
    {
        m_bRunFlag = false;
        ConnectionLost();
    }
    return;
}

bool TcpClient::Send(byte* pbyData, size_t uDataLen)
{
    bool bResult = false;
    int nRetCode = 0;
    timeval timeout{0, 0};

    JY_PROCESS_ERROR(m_bRunFlag);
    JYLOG_PROCESS_ERROR(pbyData);

    while (uDataLen > 0)
    {
        nRetCode = CanSend(m_Socket, &timeout);
        JYLOG_PROCESS_ERROR(nRetCode != 0);
        if (nRetCode < 0)
        {
            JY_PROCESS_CONTINUE(SocketCanRestore());
            goto Exit0;
        }

        nRetCode = send(m_Socket, (char*)pbyData, uDataLen, 0);
        JYLOG_PROCESS_ERROR(nRetCode != 0);

        if (nRetCode < 0)
        {
            JY_PROCESS_CONTINUE(SocketCanRestore());
            goto Exit0;
        }

        pbyData += nRetCode;
        uDataLen -= nRetCode;
    }

    bResult = true;
Exit0:
    if (!bResult && m_bRunFlag)
    {
        m_bRunFlag = false;
        ConnectionLost();
    }
    return bResult;
}
bool TcpClient::IsEnable()
{
    return m_bRunFlag;
}