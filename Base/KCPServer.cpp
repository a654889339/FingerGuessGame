#include "stdafx.h"
#include "KCPServer.h"


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

		pszRecvFD = AcceptConnection();
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
	ClientAddr* pClientAddr;

	JY_PROCESS_ERROR(m_bRunFlag);
	JYLOG_PROCESS_ERROR(IsAlive(nConnIndex));
	JYLOG_PROCESS_ERROR(pbyData);

	pClientAddr = GetClientSocket(nConnIndex);
	JY_PROCESS_ERROR(pClientAddr->bValid);

	// Async + encrypt + Compress
	JYLOG_PROCESS_ERROR(uDataLen + 2 < sizeof(m_szSendBuffer));

	*(WORD*)m_szSendBuffer = (WORD)uDataLen;
	memcpy(m_szSendBuffer + 2, pbyData, uDataLen);

	bRetCode = _Send(ClientSocket, m_szSendBuffer, uDataLen + 2);
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
	ClientAddr* pClientAddr = GetClientSocket(nConnIndex);
	return pClientAddr && pClientAddr->bValid;
}

ClientAddr* KCPServer::GetClientSocket(int nConnIndex)
{
	ClientAddr* Result = NULL;

	JYLOG_PROCESS_ERROR(nConnIndex >= 0 && nConnIndex < MAX_ACCEPT_CONNECTION);

	Result = &m_nConnecFlag[nConnIndex];
Exit0:
	return Result;
}
