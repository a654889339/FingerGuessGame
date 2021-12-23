#include "stdafx.h"
#include "ClientASServer.h"
#include "AccountServer.h"

ClientASServer::ClientASServer()
{
    memset(m_ProcessProtocolFuns, 0, sizeof(m_ProcessProtocolFuns));
    memset(m_nProtocolSize, 0, sizeof(m_nProtocolSize));

    REGISTER_EXTERNAL_FUNC(ec2as_login_request, &ClientASServer::OnC2ASLoginRequest, sizeof(C2AS_LOGIN_REQUEST));
}

ClientASServer::~ClientASServer()
{

}

bool ClientASServer::Init()
{
    bool bResult  = false;
    bool bRetCode = false;

    bRetCode = Bind(CLIENT_ACCOUNT_SERVER_LISTEN_IP, CLIENT_ACCOUNT_SERVER_LISTEN_PORT);
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_BOOL_END
}

void ClientASServer::UnInit()
{
    Quit();
}

void ClientASServer::Active()
{
    ProcessNetwork();
}

bool ClientASServer::DoAS2CLoginRespond(int nConnIndex, int nRetCode)
{
    bool                bResult  = false;
    bool                bRetCode = false;
    AS2C_LOGIN_RESPOND* pRespond = (AS2C_LOGIN_RESPOND*)GetSendBuffer(sizeof(AS2C_LOGIN_RESPOND));

    JYLOG_PROCESS_ERROR(pRespond);

    pRespond->wProtocolID = eas2c_login_respond;
    pRespond->nResultCode = nRetCode;

    bRetCode = Send(nConnIndex, pRespond, sizeof(AS2C_LOGIN_RESPOND));
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_BOOL_END
}

//////////////////////////////////////////////////////////////////////////

void ClientASServer::ProcessPackage(int nConnIndex, BYTE* pbyData, size_t uDataLen)
{
    PROTOCOL_HEADER*      pHeader = (PROTOCOL_HEADER*)pbyData;
    PROCESS_PROTOCOL_FUNC Func    = NULL;

    JYLOG_PROCESS_ERROR(pbyData);
    JYLOG_PROCESS_ERROR(uDataLen >= sizeof(PROTOCOL_HEADER));
    JYLOG_PROCESS_ERROR(ec2as_begin < pHeader->wProtocolID&& pHeader->wProtocolID < ec2as_end);

    if (m_nProtocolSize[pHeader->wProtocolID] != UNDEFINED_PROTOCOL_SIZE)
    {
        JYLOG_PROCESS_ERROR(uDataLen == m_nProtocolSize[pHeader->wProtocolID]);
    }

    Func = m_ProcessProtocolFuns[pHeader->wProtocolID];
    JYLOG_PROCESS_ERROR(Func);

    (this->*Func)(nConnIndex, pbyData, uDataLen);

    JY_STD_VOID_END;
}

void ClientASServer::NewConnection(int nConnIndex, int* pnIP, int nPort)
{
    printf("[ASClientAgent] NewConnection %d, IP: %s, Port: %d\n", nConnIndex, inet_ntoa(*(in_addr*)pnIP), nPort);
    m_ConnManager[nConnIndex] = ConnectionInfo(*pnIP, nPort);
}

void ClientASServer::DisConnection(int nConnIndex)
{
    printf("[ASClientAgent] DisConnection %d, IP: %d, Port: %d\n", nConnIndex, m_ConnManager[nConnIndex].nIP, m_ConnManager[nConnIndex].nPort);
    g_pAccountServer->m_ClientManager.Del(nConnIndex);
    m_ConnManager.remove(nConnIndex);
}

void ClientASServer::OnC2ASLoginRequest(int nConnIndex, BYTE* pbyData, size_t uDataLen)
{
    int                 nResult  = elrc_invalid;
    bool                bRetCode = false;
    C2AS_LOGIN_REQUEST* pRequest = (C2AS_LOGIN_REQUEST*)pbyData;

    JY_PROCESS_ERROR_RET_CODE(pRequest->nAccountServerVersion == ACCOUNT_SERVER_VERSION, elrc_version_error);

    bRetCode = g_pAccountServer->m_ClientManager.Add(pRequest->szAccountName, nConnIndex);
    JY_PROCESS_ERROR_RET_CODE(bRetCode, elrc_account_repeat);

    DoAS2CLoginRespond(nConnIndex, elrc_success);

    nResult = elrc_success;
Exit0:
    if (nResult != elrc_success)
    {
        DoAS2CLoginRespond(nConnIndex, nResult);
        Shutdown(nConnIndex);
    }
    return ;
}