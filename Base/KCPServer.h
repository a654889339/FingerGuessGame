#ifndef _KCP_SERVER_H_
#define _KCP_SERVER_H_


#include "NetworkBase.h"
#include <map>
#ifdef _SERVER
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

struct AddrCmp 
{
	bool operator()(const sockaddr_in& Addr_A, const sockaddr_in& Addr_B) const
	{
		return  Addr_A.sin_addr.S_un.S_addr < Addr_B.sin_addr.S_un.S_addr || Addr_A.sin_addr.S_un.S_addr == Addr_B.sin_addr.S_un.S_addr && Addr_A.sin_port < Addr_B.sin_port;
	}
};

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
	KCPRecvFD* AcceptConnection(sockaddr_in&);
	bool IsAlive(int nConnIndex);
	KCPRecvFD* GetClientSocket(int nConnIndex);
private:
	SOCKET m_Socket;
	bool m_bRunFlag;
	KCPRecvFD m_nConnecFlag[MAX_ACCEPT_CONNECTION];

	char m_szRecvBuffer[MAX_RECV_BUFFER_SIZE];
	char m_szSendBuffer[MAX_RECV_BUFFER_SIZE];

	std::map<sockaddr_in, KCPRecvFD*, AddrCmp> m_ClientManager;
};
  
#endif
#endif