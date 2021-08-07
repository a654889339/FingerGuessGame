#include "stdafx.h"
#include "TcpServer.h"

TcpServer::TcpServer()
{
    m_Socket = INVALID_SOCKET;
    m_bRunFlag = false;
    InitNetwork();
    FD_ZERO(&m_SocketReadSet);

    memset(m_szRecvBuffer, 0, sizeof(m_szRecvBuffer));
}

TcpServer::~TcpServer()
{
    Close();
    UnInitNetwork();
}

bool TcpServer::Bind(const char szIP[], int nPort)
{
    bool bResult = false;
    int nRetCode = 0;
    sockaddr_in sin;

    m_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    JYLOG_PROCESS_ERROR(m_Socket != INVALID_SOCKET);

    sin.sin_family = AF_INET;
    sin.sin_port = htons(nPort);
    sin.sin_addr.S_un.S_addr = inet_addr(szIP);

    nRetCode = bind(m_Socket, (LPSOCKADDR)&sin, sizeof(sin));
    JYLOG_PROCESS_ERROR(nRetCode != SOCKET_ERROR);

    nRetCode = listen(m_Socket, MAX_ACCEPT_CONNECTION);
    JYLOG_PROCESS_ERROR(nRetCode != SOCKET_ERROR);

    FD_SET(m_Socket, &m_SocketReadSet);

    m_bRunFlag = true;

    JY_STD_BOOL_END
}

void TcpServer::ProcessNetwork()
{
    bool bResult = false;
    int nRetCode = 0;
    RecvFD* pszRecvFD = NULL;
    timeval timeout{ 0,0 };
    FD_SET CheckFD;

    JY_PROCESS_SUCCESS(!m_bRunFlag);
    FD_ZERO(&CheckFD);
    CheckFD = m_SocketReadSet;

    nRetCode = select(0, &CheckFD, nullptr, nullptr, &timeout);
    JY_PROCESS_ERROR(nRetCode != SOCKET_ERROR);

    for (int i = 0; i < (int)CheckFD.fd_count; i++)
    {
        pszRecvFD = GetRecvFD(i);
        JYLOG_PROCESS_CONTINUE(pszRecvFD);

        SOCKET CheckSocket = CheckFD.fd_array[i];
        if (CheckSocket == m_Socket)
        {
            SOCKET NewClient;
            sockaddr_in remoteAddr;
            int nAddrlen = sizeof(remoteAddr);

            NewClient = accept(m_Socket, (SOCKADDR*)&remoteAddr, &nAddrlen);
            JYLOG_PROCESS_CONTINUE(NewClient != INVALID_SOCKET);
            FD_SET(NewClient, &m_SocketReadSet);

            pszRecvFD->Clear();
            pszRecvFD->bConnFlag = true;

            NewConnection(i, inet_ntoa(remoteAddr.sin_addr), remoteAddr.sin_port);
        }
        else
        {
            nRetCode = recv(CheckSocket, m_szRecvBuffer, sizeof(m_szRecvBuffer), 0);
            if (nRetCode == SOCKET_ERROR || nRetCode == 0)
            {
                pszRecvFD->bConnFlag = false;
                closesocket(CheckSocket);
                FD_CLR(CheckSocket, &m_SocketReadSet);
                DisConnection(i);
            }
            else
            {
                if (GetFullPackage(pszRecvFD, m_szRecvBuffer))
                    ProcessPackage(i, (byte*)m_szRecvBuffer, pszRecvFD->uProtoSize);
            }
        }
    }

Exit1:
    bResult = true;
Exit0:
    if (!bResult)
    {
        Close();
    }
    return;
}

bool TcpServer::Send(int nConnIndex, void* pbyData, size_t uDataLen)
{
    bool bResult = false;
    bool bRetCode = false;
    SOCKET ClientSocket = INVALID_SOCKET;

    JY_PROCESS_ERROR(m_bRunFlag);
    JYLOG_PROCESS_ERROR(IsAlive(nConnIndex));
    JYLOG_PROCESS_ERROR(pbyData);

    // Async
    JYLOG_PROCESS_ERROR(uDataLen + 2 < sizeof(m_szSendBuffer));

    *(WORD*)m_szSendBuffer = (WORD)uDataLen;
    memcpy(m_szSendBuffer + 2, pbyData, uDataLen);

    bRetCode = _Send(m_SocketReadSet.fd_array[nConnIndex], m_szSendBuffer, uDataLen + 2);
    JYLOG_PROCESS_ERROR(bRetCode);

    bResult = true;
Exit0:
    if (!bResult && m_bRunFlag)
    {
        DisConnection(nConnIndex);
    }
    return bResult;
}

void TcpServer::Close()
{
    if (m_bRunFlag)
    {
        m_bRunFlag = false;
        closesocket(m_Socket);
        FD_ZERO(&m_SocketReadSet);
    }
}
//////////////////////////////////////////////////////////////////////////
RecvFD* TcpServer::GetRecvFD(int nConnIndex)
{
    RecvFD* pResult = NULL;

    JYLOG_PROCESS_ERROR(nConnIndex >= 0 && nConnIndex < MAX_ACCEPT_CONNECTION);

    pResult = &m_szRecvFD[nConnIndex];
Exit0:
    return pResult;
}

bool TcpServer::IsAlive(int nConnIndex)
{
    bool bResult = false;
    RecvFD* pClientFD = NULL;

    pClientFD = GetRecvFD(nConnIndex);
    JY_PROCESS_ERROR(pClientFD);
    JY_PROCESS_ERROR(pClientFD->bConnFlag);

    bResult = true;
Exit0:
    return bResult;
}