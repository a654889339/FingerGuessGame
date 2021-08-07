#include "stdafx.h"
#include "ClientConnection.h"
#include "ClientWorld.h"

#define REGISTER_EXTERNAL_FUNC(ProtocolID, FuncName, ProtocolSize)  \
{m_ProcessProtocolFuns[ProtocolID] = FuncName;                  \
    m_nProtocolSize[ProtocolID] = ProtocolSize;}

ClientConnection::ClientConnection()
{

    memset(m_ProcessProtocolFuns, 0, sizeof(m_ProcessProtocolFuns));
    memset(m_nProtocolSize, 0, sizeof(m_nProtocolSize));

    REGISTER_EXTERNAL_FUNC(s2c_handshake_respond, &ClientConnection::OnS2CHandshakeRespond, sizeof(S2C_HANDSHAKE_RESPOND));
}

ClientConnection::~ClientConnection()
{

}

bool ClientConnection::Init(const char szIP[], int nPort)
{
    bool bResult = false;
    bool bRetCode = false;

    JYLOG_PROCESS_ERROR(szIP);

    bRetCode = Connect(szIP, nPort);
    JYLOG_PROCESS_ERROR(bRetCode);

    bRetCode = DoS2CHandshakeRequest();
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_BOOL_END
}

void ClientConnection::UnInit()
{

}

void ClientConnection::Active()
{
    ProcessNetwork();
}

void ClientConnection::DisConnect()
{

}

bool ClientConnection::DoS2CHandshakeRequest()
{
    bool bResult = false;
    bool bRetCode = false;
    C2S_HANDSHAKE_REQUEST Request;

    bRetCode = Send((byte*)&Request, sizeof(Request));
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_BOOL_END
}

// Private
void ClientConnection::OnS2CHandshakeRespond(BYTE* pbyData, size_t uSize)
{
    S2C_HANDSHAKE_RESPOND* pRespond = (S2C_HANDSHAKE_RESPOND*)pbyData;

    JYLOG_PROCESS_ERROR(pRespond);

    if (pRespond->bSuccess)
    {

    }
    else
    {
        Close();
        g_pClient->Quit();
    }

    JY_STD_VOID_END
}

void ClientConnection::ProcessPackage(byte* pbyData, size_t uDataLen)
{
    PROTOCOL_HEADER* pHeader = (PROTOCOL_HEADER*)pbyData;
    PROCESS_PROTOCOL_FUNC Func = NULL;

    JYLOG_PROCESS_ERROR(pbyData);
    JYLOG_PROCESS_ERROR(uDataLen >= sizeof(PROTOCOL_HEADER));
    JYLOG_PROCESS_ERROR(s2c_begin < pHeader->wProtocolID && pHeader->wProtocolID < s2c_end);

    uDataLen -= sizeof(PROTOCOL_HEADER);
    if (m_nProtocolSize[pHeader->wProtocolID] != UNDEFINED_PROTOCOL_SIZE)
    {
        JYLOG_PROCESS_ERROR(uDataLen == m_nProtocolSize[pHeader->wProtocolID]);
    }

    Func = m_ProcessProtocolFuns[pHeader->wProtocolID];
    JYLOG_PROCESS_ERROR(Func);

    (this->*Func)(pbyData, uDataLen);

    JY_STD_VOID_END;
}

void ClientConnection::ConnectionLost()
{

}