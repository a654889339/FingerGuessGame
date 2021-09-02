#include "stdafx.h"
#include "KCPServer.h"

KCPServer::KCPServer()
{
  
	m_Socket = INVALID_SOCKET;
	m_bRunFlag = false;
	_InitNetwork();
	FD_ZERO(&m_SocketReadSet);

	memset(m_nConnecFlag, -1, sizeof(m_nConnecFlag));
}

KCPServer::~KCPServer()
{
	Quit();
	_UnInitNetwork();
}

bool KCPServer::Bind(const char szIP[], int nPort)
{
	bool bResult = false;
	int nRetCode = 0;
	sockaddr_in sin;

	int n = m_Socket;

	m_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_UDP);
	JYLOG_PROCESS_ERROR(m_Socket != INVALID_SOCKET);

	sin.sin_family = AF_INET;
	sin.sin_port = htons(nPort);
	sin.sin_addr.S_un.S_addr = inet_addr(szIP);

	nRetCode = bind(m_Socket, (LPSOCKADDR)&sin, sizeof(sin));
	JYLOG_PROCESS_ERROR(nRetCode != SOCKET_ERROR);

	FD_SET(m_Socket, &m_SocketReadSet);

	m_bRunFlag = true;

	JY_STD_BOOL_END
}

void KCPServer::ProcessNetwork()
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
			else if (_GetFullPackage(pszRecvFD, m_szRecvBuffer))
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