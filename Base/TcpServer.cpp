#include "stdafx.h"
#include "TcpServer.h"

TcpServer::TcpServer()
{
    InitNetwork();
    FD_ZERO(&m_SocketReadSet);
}

TcpServer::~TcpServer()
{
    if (m_bRunFlag)
        closesocket(m_Socket);

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
    RecvFD* pszRecvFD = NULL;
    timeval timeout{ 0,0 };
    FD_SET CheckFD;

    JY_PROCESS_ERROR(m_bRunFlag);
    while (true)
    {
        FD_ZERO(&CheckFD);
        CheckFD = m_SocketReadSet;


        int total = select(0, &CheckFD, nullptr, nullptr, &timeout);
        JY_PROCESS_CONTINUE(total != SOCKET_ERROR);

        for (int i = 0; i < CheckFD.fd_count; i++)
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
                int ret = recv(CheckSocket, m_szRecvBuffer, sizeof(m_szRecvBuffer), 0);
                if (ret == SOCKET_ERROR || ret == 0)
                {
                    pszRecvFD->bConnFlag = false;
                    DisConnection(i);
                    closesocket(CheckSocket);
                    FD_CLR(CheckSocket, &m_SocketReadSet);
                }
                else
                {
                    ProcessPackage(i, m_szRecvBuffer, )
                }
            }
        }
    }

    JY_STD_VOID_END
}

RecvFD* TcpServer::GetRecvFD(int nConnIndex)
{
    RecvFD* pResult = NULL;

    JY_PROCESS_CONTINUE(nConnIndex >= 0 && nConnIndex < MAX_ACCEPT_CONNECTION);

    pResult = &m_szRecvFD[nConnIndex];
Exit0:
    return pResult;
}