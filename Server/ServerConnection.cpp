#include "stdafx.h"
#include "ServerConnection.h"
#include "ServerWorld.h"

#define REGISTER_EXTERNAL_FUNC(ProtocolID, FuncName, ProtocolSize)  \
{m_ProcessProtocolFuns[ProtocolID] = FuncName;                  \
    m_nProtocolSize[ProtocolID] = ProtocolSize;}

ServerConnection::ServerConnection()
{

    memset(m_ProcessProtocolFuns, 0, sizeof(m_ProcessProtocolFuns));
    memset(m_nProtocolSize, 0, sizeof(m_nProtocolSize));

    REGISTER_EXTERNAL_FUNC(c2s_handshake_request, &ServerConnection::OnC2SHandshakeRequest, sizeof(C2S_HANDSHAKE_REQUEST));
}
ServerConnection::~ServerConnection()
{

}

bool ServerConnection::Init(const char szIP[], int nPort)
{
    bool bResult = false;
    bool bRetCode = false;

    bRetCode = Bind(szIP, nPort);
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_BOOL_END
}

void ServerConnection::UnInit()
{

}

void ServerConnection::Active()
{

}

bool ServerConnection::DoS2CHandshakeRespond(int nConnIndex, bool bSuccess)
{
    bool bResult = false;
    bool bRetCode = false;
    S2C_HANDSHAKE_RESPOND Respond;

    Respond.wProtocolID = s2c_handshake_respond;
    Respond.bSuccess = bSuccess;

    bRetCode = Send(nConnIndex, &Respond, sizeof(Respond));
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_BOOL_END
}

//////////////////////////////////////////////////////////////////////////

void ServerConnection::OnC2SHandshakeRequest(int nConnIndex, byte* pbyData, size_t uDataLen)
{
    bool                   bResult = false;
    bool                   bRetCode = false;
    C2S_HANDSHAKE_REQUEST* pRequest = (C2S_HANDSHAKE_REQUEST*)pbyData;

    bRetCode = bRetCode = g_pServer->m_PlayerManager.AddPlayer(nConnIndex, pRequest->szName);
    JY_PROCESS_ERROR(bRetCode);

    
    bResult = true;
Exit0:
    DoS2CHandshakeRespond(nConnIndex, bResult);
    return;
}

void ServerConnection::ProcessPackage(int nConnIndex, byte* pbyData, size_t uDataLen)
{
    PROTOCOL_HEADER* pHeader = (PROTOCOL_HEADER*)pbyData;
    PROCESS_PROTOCOL_FUNC Func = NULL;

    JYLOG_PROCESS_ERROR(pbyData);
    JYLOG_PROCESS_ERROR(uDataLen >= sizeof(PROTOCOL_HEADER));
    JYLOG_PROCESS_ERROR(c2s_begin < pHeader->wProtocolID && pHeader->wProtocolID < c2s_end);

    uDataLen -= sizeof(PROTOCOL_HEADER);
    if (m_nProtocolSize[pHeader->wProtocolID] != UNDEFINED_PROTOCOL_SIZE)
    {
        JYLOG_PROCESS_ERROR(uDataLen == m_nProtocolSize[pHeader->wProtocolID]);
    }

    Func = m_ProcessProtocolFuns[pHeader->wProtocolID];
    JYLOG_PROCESS_ERROR(Func);

    (this->*Func)(nConnIndex, pbyData, uDataLen);

    JY_STD_VOID_END;
}

void ServerConnection::NewConnection(int nConnIndex, const char szIP[], int nPort)
{

}

void ServerConnection::DisConnection(int nConnIndex)
{

}