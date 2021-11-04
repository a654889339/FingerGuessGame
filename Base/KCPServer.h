#ifndef _KCP_SERVER_H_
#define _KCP_SERVER_H_

#include "NetworkBase.h"


#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

struct ClientAddr 
{
	sockaddr_in addr_in;
	bool bValid;
	bool operator < (const ClientAddr& clientAdrr) const
	{
		return  addr_in.sin_addr.S_un.S_addr < clientAdrr.addr_in.sin_addr.S_un.S_addr || addr_in.sin_addr.S_un.S_addr == clientAdrr.addr_in.sin_addr.S_un.S_addr && addr_in.sin_port < clientAdrr.addr_in.sin_port;
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
	KCPRecvFD* AcceptConnection();
	bool IsAlive(int nConnIndex);
	ClientAddr* GetClientSocket(int nConnIndex);
private:
	SOCKET m_Socket;
	bool m_bRunFlag;
	ClientAddr m_nConnecFlag[MAX_ACCEPT_CONNECTION];

	char m_szRecvBuffer[MAX_RECV_BUFFER_SIZE];
	char m_szSendBuffer[MAX_RECV_BUFFER_SIZE];

	typedef SplayTree<ClientAddr, KCPRecvFD> CLIENT_INDEX_MANAGER;
	CLIENT_INDEX_MANAGER m_ClientManager;
};
  
#endif
