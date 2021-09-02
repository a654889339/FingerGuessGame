#ifndef _KCP_SERVER_H_
#define _KCP_SERVER_H_

#include "NetworkBase.h"

#ifdef _SERVER
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif
class KCPServer
{
public:
    KCPServer();
    virtual ~KCPServer();
	virtual bool Bind(const char szIP[], int nPort) final;

	virtual void ProcessNetwork() final;
	virtual bool Send(int nConnIndex, void* pbyData, size_t uDataLen) final;
	virtual bool IsEnable() final;
	virtual void Quit() final;
	virtual void Shutdown(int nConnIndex) final;

	virtual void ProcessPackage(int nConnIndex, byte* pbyData, size_t uDataLen) = 0;
	virtual void NewConnection(int nConnIndex, const char szIP[], int nPort) = 0;
	virtual void DisConnection(int nConnIndex) = 0;
private:


	SOCKET m_Socket;
	bool m_bRunFlag;
	FD_SET  m_SocketReadSet;
	int m_nConnecFlag[MAX_ACCEPT_CONNECTION];

	char m_szRecvBuffer[MAX_RECV_BUFFER_SIZE];
	char m_szSendBuffer[MAX_RECV_BUFFER_SIZE];
};
  
#endif
#endif