#include "stdafx.h"
#include "KCPClient.h"
#pragma comment(lib,"ws2_32.lib")
KCPClient::KCPClient()
{
	m_bRunFlag = false;
}

KCPClient::~KCPClient()
{

}

bool KCPClient::Init(const char szIP[], int nPort)
{
    BOOL bResult = false;
	int nResCode = 0;
    JYLOG_PROCESS_ERROR(szIP);
    JYLOG_PROCESS_ERROR(nPort);
	WSADATA wsaData;
	//初始化Socket
	nResCode = WSAStartup(MAKEWORD(2, 2), &wsaData);
	JYLOG_PROCESS_ERROR(nResCode == 0);
	//创建Socket对象
	m_Socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	//设置服务器地址
	m_SerAddr.sin_family = AF_INET;
	m_SerAddr.sin_port = htons(nPort);
	m_SerAddr.sin_addr.S_un.S_addr = inet_addr(szIP);
	//向服务器发送数据报
	//printf("Sending a datagram to the receiver...\n");
	//sendto(m_Socket, SendBuf, BufLen, 0, (SOCKADDR*)&serAddr, sizeof(RecvAddr));

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
	bRetCode = sendto(m_Socket, m_szSendBuffer, uDataLen + 2, 0, (SOCKADDR*)&m_SerAddr, sizeof(SOCKADDR));
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