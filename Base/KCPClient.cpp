#include "stdafx.h"
#include "KCPClient.h"
//#pragma comment(lib,"ws2_32.lib")
KCPClient::KCPClient()
{
	m_bRunFlag = false;
	memset(m_szRecvBuffer, 0, sizeof(m_szRecvBuffer));
	_InitNetwork();
}

KCPClient::~KCPClient()
{
	Quit();
	_UnInitNetwork();
}

bool KCPClient::Init(const char szIP[], int nPort)
{
    BOOL bResult = false;
	int nResCode = 0;
    JYLOG_PROCESS_ERROR(szIP);
    JYLOG_PROCESS_ERROR(nPort);

	m_Socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	JYLOG_PROCESS_ERROR(m_Socket != INVALID_SOCKET);
	m_SerAddr.sin_family = AF_INET;
	m_SerAddr.sin_port = htons(nPort);
	m_SerAddr.sin_addr.S_un.S_addr = inet_addr(szIP);

    bResult = true;
Exit0:
    return bResult;
}

bool KCPClient::Send(void* pbyData, size_t uDataLen)
{
	bool bResult = false;
	bool bRetCode = false;

	JY_PROCESS_SUCCESS(!m_bRunFlag);
	JYLOG_PROCESS_ERROR(pbyData);

	// Async + encrypt + Compress
	JYLOG_PROCESS_ERROR(uDataLen + 2 < sizeof(m_szSendBuffer));

	*(WORD*)m_szSendBuffer = (WORD)uDataLen;
	memcpy(m_szSendBuffer + 2, pbyData, uDataLen);
	bRetCode = sendto(m_Socket, m_szSendBuffer, uDataLen + 2, 0, (SOCKADDR*)&m_SerAddr, sizeof(m_SerAddr));
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

void KCPClient::ProcessNetwork()
{
	bool bResult = false;
	bool bRetCode = false;
	int nRetCode = 0;
	int nRecvLength = 0;
	JY_PROCESS_SUCCESS(!m_bRunFlag);
	nRetCode = recvfrom(m_Socket, m_szRecvBuffer, sizeof(m_szRecvBuffer), 0, (SOCKADDR*)&m_RecvAddr, &nRecvLength);

	JY_PROCESS_SUCCESS(nRetCode != SOCKET_ERROR);
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

bool KCPClient::IsEnable()
{
	return m_bRunFlag;
}

void KCPClient::Quit()
{
	if (m_bRunFlag)
	{
		m_bRunFlag = false;
		closesocket(m_Socket);
	}
}
