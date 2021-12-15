#include "stdafx.h"
#include "TcpServer.h"

#ifdef _SERVER

TcpServer::TcpServer()
{
    m_Socket = INVALID_SOCKET;
    m_bRunFlag = false;
    _InitNetwork();
    FD_ZERO(&m_SocketReadSet);

    for (int i = 0; i < MAX_ACCEPT_CONNECTION; i++)
        m_nConnecFlag[i] = INVALID_SOCKET;
}

TcpServer::~TcpServer()
{
    Quit();
    _UnInitNetwork();
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
    bool bRetCode = false;
    int nRetCode = 0;
    RecvFD* pszRecvFD = NULL;
    timeval timeout{ 0,0 };
    time_t nTimeNow = time(NULL);
    FD_SET CheckFD;

    JY_PROCESS_SUCCESS(!m_bRunFlag);
    FD_ZERO(&CheckFD);
    CheckFD = m_SocketReadSet;

    nRetCode = select(0, &CheckFD, nullptr, nullptr, &timeout);
    JYLOG_PROCESS_ERROR(nRetCode != SOCKET_ERROR);

    for (int i = 0; i < (int)CheckFD.fd_count; i++)
    {
        SOCKET ClientSocket = CheckFD.fd_array[i];
        if (ClientSocket == m_Socket)
        {
            JYLOG_PROCESS_CONTINUE(m_SocketReadSet.fd_count < MAX_ACCEPT_CONNECTION);

            AcceptConnection();
        }
        else
        {
            pszRecvFD = m_ClientManager.find(ClientSocket);
            JYLOG_PROCESS_CONTINUE(pszRecvFD);

            if (pszRecvFD->nActiveTime + CONNECTION_TIME_OUT < nTimeNow)
            {
                printf("[ProcessNetwork] Timeout:%d.\n", pszRecvFD->nConnIndex);
                Shutdown(pszRecvFD->nConnIndex);
                continue;
            }

            nRetCode = _CanRecv(ClientSocket);
            JY_TRUE_CONTINUE(nRetCode == 0);
            if (nRetCode < 0)
            {
                JY_TRUE_CONTINUE(_SocketCanRestore());

                Shutdown(pszRecvFD->nConnIndex);
                continue;
            }

            nRetCode = recv(ClientSocket, m_szRecvBuffer, sizeof(m_szRecvBuffer), 0);
            JY_TRUE_CONTINUE(nRetCode == 0);

            if (nRetCode < 0)
            {
                JY_TRUE_CONTINUE(_SocketCanRestore());

                Shutdown(pszRecvFD->nConnIndex);
                continue;
            }

            pszRecvFD->nActiveTime = nTimeNow;
            bRetCode = pszRecvFD->RecvQueue.push(m_szRecvBuffer, (size_t)nRetCode);
            if (!bRetCode)
                Shutdown(pszRecvFD->nConnIndex);
            else if (_TCPGetFullPackage(pszRecvFD, m_szRecvBuffer))
                ProcessPackage(pszRecvFD->nConnIndex, (byte*)m_szRecvBuffer, pszRecvFD->uProtoSize);
        }
    }

Exit1:
    bResult = true;
Exit0:
    if (!bResult)
    {
        Quit();
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

    ClientSocket = GetClientSocket(nConnIndex);
    JY_PROCESS_ERROR(ClientSocket != INVALID_SOCKET);

    // Async + encrypt + Compress
    JYLOG_PROCESS_ERROR(uDataLen + 2 < sizeof(m_szSendBuffer));

    *(WORD*)m_szSendBuffer = (WORD)uDataLen;
    memcpy(m_szSendBuffer + 2, pbyData, uDataLen);

    bRetCode = _TCPSend(ClientSocket, m_szSendBuffer, uDataLen + 2);
    JYLOG_PROCESS_ERROR(bRetCode);

    bResult = true;
Exit0:
    if (!bResult && m_bRunFlag)
    {
        Shutdown(nConnIndex);
    }
    return bResult;
}

bool TcpServer::IsEnable()
{
    return m_bRunFlag;
}

void TcpServer::Quit()
{
    JY_PROCESS_ERROR(m_bRunFlag);

    m_bRunFlag = false;

    m_ClientManager.clear();

    for (int i = 0; i < MAX_ACCEPT_CONNECTION; i++)
        if (m_nConnecFlag[i] != INVALID_SOCKET)
            closesocket(m_nConnecFlag[i]);

    closesocket(m_Socket);
    FD_ZERO(&m_SocketReadSet);

    JY_STD_VOID_END
}

void TcpServer::Shutdown(int nConnIndex)
{
    SOCKET ClientSocket = INVALID_SOCKET;

    JY_PROCESS_ERROR(m_bRunFlag);

    ClientSocket = GetClientSocket(nConnIndex);
    JY_PROCESS_ERROR(ClientSocket != INVALID_SOCKET);

    m_ClientManager.remove(ClientSocket);
    closesocket(ClientSocket);
    FD_CLR(ClientSocket, &m_SocketReadSet);
    m_nConnecFlag[nConnIndex] = INVALID_SOCKET;

    DisConnection(nConnIndex);

    JY_STD_VOID_END
}
//////////////////////////////////////////////////////////////////////////
void TcpServer::AcceptConnection()
{
    int nConnIndex = INVALID_CONNINDEX;
    int nAddrlen = 0;
    RecvFD* pszRecvFD = NULL;
    SOCKET NewClient = INVALID_SOCKET;
    sockaddr_in remoteAddr;

    for (int i = 0; i < MAX_ACCEPT_CONNECTION; i++)
    {
        if (m_nConnecFlag[i] == INVALID_SOCKET)
        {
            nConnIndex = i;
            break;
        }
    }
    JYLOG_PROCESS_ERROR(nConnIndex != INVALID_CONNINDEX);

    nAddrlen = sizeof(remoteAddr);

    NewClient = accept(m_Socket, (SOCKADDR*)&remoteAddr, &nAddrlen);
    JYLOG_PROCESS_ERROR(NewClient != INVALID_SOCKET);

    pszRecvFD = m_ClientManager.add(NewClient);
    JYLOG_PROCESS_ERROR(pszRecvFD);

    pszRecvFD->Connect(NewClient, nConnIndex);

    m_nConnecFlag[nConnIndex] = NewClient;
    FD_SET(NewClient, &m_SocketReadSet);

    NewConnection(nConnIndex, inet_ntoa(remoteAddr.sin_addr), remoteAddr.sin_port);

    JY_STD_VOID_END
}

RecvFD* TcpServer::GetClientFD(int nConnIndex)
{
    RecvFD* pResult = NULL;
    SOCKET ClientSocket = INVALID_SOCKET;

    ClientSocket = GetClientSocket(nConnIndex);
    JY_PROCESS_ERROR(ClientSocket != INVALID_SOCKET);

    pResult = m_ClientManager.find(ClientSocket);
Exit0:
    return pResult;
}

SOCKET TcpServer::GetClientSocket(int nConnIndex)
{
    SOCKET Result = INVALID_SOCKET;

    JYLOG_PROCESS_ERROR(nConnIndex >= 0 && nConnIndex < MAX_ACCEPT_CONNECTION);

    Result = m_nConnecFlag[nConnIndex];
Exit0:
    return Result;
}

bool TcpServer::IsAlive(int nConnIndex)
{
    return GetClientSocket(nConnIndex) != INVALID_SOCKET;
}

#endif