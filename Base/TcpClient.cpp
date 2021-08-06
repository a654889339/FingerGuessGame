#include "stdafx.h"
#include "TcpClient.h"

TcpClient::TcpClient()
{
    m_bRunFlag = false;
    m_bHaveProtoSize = false;
    m_uProtoSize = 0;
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
        int ret = recv(m_Socket, m_szRecvBuffer, min(m_RecvQueue.res_size(), sizeof(m_szRecvBuffer)), 0);
        if (ret > 0)
        {
            bRetCode = m_RecvQueue.push(m_szRecvBuffer, ret);
            JYLOG_PROCESS_ERROR(bRetCode);

            if (HaveFullPackage())
            {
                ProcessPackage((byte*)m_szRecvBuffer, m_uProtoSize);
            }
        }
    }

    bResult = true;
Exit0:
    if (!bResult && m_bRunFlag)
    {
        m_bRunFlag = false;
        DisConnection();
    }
    return;
}


bool TcpClient::HaveFullPackage()
{
    bool bResult = false;
    bool bRetCode = false;

    JY_PROCESS_ERROR(m_bRunFlag);

    if (m_bHaveProtoSize)
    {
        JY_PROCESS_ERROR(m_RecvQueue.size() >= m_uProtoSize);

        bRetCode = m_RecvQueue.pop(m_uProtoSize, m_szRecvBuffer);
        JYLOG_PROCESS_ERROR(bRetCode);
    }
    else
    {
        JY_PROCESS_ERROR(m_RecvQueue.size() >= 2);
        m_bHaveProtoSize = true;

        bRetCode = m_RecvQueue.pop(2, m_szRecvBuffer);
        JYLOG_PROCESS_ERROR(bRetCode);

        m_uProtoSize = m_szRecvBuffer[0] << 8 | m_szRecvBuffer[1];
    }

    bResult = true;
Exit0:
    return bResult;
}