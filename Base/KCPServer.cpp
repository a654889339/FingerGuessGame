#include "stdafx.h"
#include "KCPServer.h"

#ifdef _SERVER
KCPServer::KCPServer()
{
  
	m_Socket = INVALID_SOCKET;
	m_bRunFlag = false;
	_InitNetwork();
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

	m_Socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	JYLOG_PROCESS_ERROR(m_Socket != INVALID_SOCKET);

	sin.sin_family = AF_INET;
	sin.sin_port = htons(nPort);
	sin.sin_addr.S_un.S_addr = inet_addr(szIP);

	nRetCode = bind(m_Socket, (LPSOCKADDR)&sin, sizeof(sin));
	JYLOG_PROCESS_ERROR(nRetCode != SOCKET_ERROR);

	m_bRunFlag = true;

	JY_STD_BOOL_END
}

void KCPServer::ProcessNetwork()
{
	bool bResult = false;
	bool bRetCode = false;
	int nRetCode = 0;

	KCPRecvFD* pszRecvFD = NULL;
	timeval timeout{ 0,0 };
	time_t nTimeNow = time(NULL);
	FD_SET CheckFD;
	sockaddr_in AddrClient;
	int nAddrClientLen = sizeof(sockaddr_in);
	JY_PROCESS_SUCCESS(!m_bRunFlag);

	while (1)
	{
		nRetCode = recvfrom(m_Socket, m_szRecvBuffer, sizeof(m_szRecvBuffer), 0, (SOCKADDR*)&AddrClient, &nAddrClientLen);
		JYLOG_PROCESS_CONTINUE(nRetCode > 0);

		pszRecvFD = AcceptConnection(AddrClient);
		JYLOG_PROCESS_CONTINUE(pszRecvFD);

		if (pszRecvFD->nActiveTime + CONNECTION_TIME_OUT < nTimeNow)
		{
			printf("[ProcessNetwork] Timeout:%d.\n", pszRecvFD->nConnIndex);
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

Exit1:
	bResult = true;
Exit0:
	if (!bResult)
	{
		Quit();
	}
	return;
}

bool KCPServer::Send(int nConnIndex, void* pbyData, size_t uDataLen)
{
	bool bResult = false;
	bool bRetCode = false;
	KCPRecvFD* pKcpFD;

	JY_PROCESS_ERROR(m_bRunFlag);
	JYLOG_PROCESS_ERROR(IsAlive(nConnIndex));
	JYLOG_PROCESS_ERROR(pbyData);

	pKcpFD = GetClientSocket(nConnIndex);
	JY_PROCESS_ERROR(pKcpFD->bConnFlag);

	// Async + encrypt + Compress
	JYLOG_PROCESS_ERROR(uDataLen + 2 < sizeof(m_szSendBuffer));

	*(WORD*)m_szSendBuffer = (WORD)uDataLen;
	memcpy(m_szSendBuffer + 2, pbyData, uDataLen);

	bRetCode = _KCPSend(m_Socket, pKcpFD, m_szSendBuffer, uDataLen + 2);
	JYLOG_PROCESS_ERROR(bRetCode);

	bResult = true;
Exit0:
	if (!bResult && m_bRunFlag)
	{
		Shutdown(nConnIndex);
	}
	return bResult;
}

bool KCPServer::IsAlive(int nConnIndex)
{
	KCPRecvFD* pKcpFD = GetClientSocket(nConnIndex);
	return pKcpFD && pKcpFD->bConnFlag;
}

KCPRecvFD* KCPServer::GetClientSocket(int nConnIndex)
{
	KCPRecvFD* pKcpFD = NULL;

	JYLOG_PROCESS_ERROR(nConnIndex >= 0 && nConnIndex < MAX_ACCEPT_CONNECTION);

	pKcpFD = &m_nConnecFlag[nConnIndex];
Exit0:
	return pKcpFD;
}

bool KCPServer::IsEnable()
{
	return m_bRunFlag;
}

void KCPServer::Quit()
{
	JY_PROCESS_ERROR(m_bRunFlag);

	m_bRunFlag = false;

	m_ClientManager.clear();

	for (int i = 0; i < MAX_ACCEPT_CONNECTION; i++)
		m_nConnecFlag[i].bConnFlag = false;

	closesocket(m_Socket);
	JY_STD_VOID_END
}

KCPRecvFD* KCPServer::AcceptConnection(sockaddr_in& RemoteAddr)
{
	int nConnIndex = INVALID_CONNINDEX;
	int nAddrlen = 0;
	KCPRecvFD* pszKCPRecvFD = NULL;

	for (int i = 0; i < MAX_ACCEPT_CONNECTION; i++)
	{
		if (!m_nConnecFlag[i].bConnFlag)
		{
			nConnIndex = i;

			break;
		}
	}
	JYLOG_PROCESS_ERROR(nConnIndex != INVALID_CONNINDEX);

	pszKCPRecvFD = &m_nConnecFlag[nConnIndex];
	pszKCPRecvFD->Connect(RemoteAddr, nConnIndex);

	nAddrlen = sizeof(RemoteAddr);

	m_ClientManager[RemoteAddr] = pszKCPRecvFD;

	NewConnection(nConnIndex, inet_ntoa(RemoteAddr.sin_addr), RemoteAddr.sin_port);
Exit0:
	return pszKCPRecvFD;
}

void KCPServer::Shutdown(int nConnIndex)
{
	KCPRecvFD* pszKCPRecvFD = NULL;

	JY_PROCESS_ERROR(m_bRunFlag);

	pszKCPRecvFD = GetClientSocket(nConnIndex);
	JY_PROCESS_ERROR(pszKCPRecvFD);

	m_ClientManager.erase(pszKCPRecvFD->Addr);

	m_nConnecFlag[nConnIndex].bConnFlag = false;

	DisConnection(nConnIndex);

	JY_STD_VOID_END
}
#endif