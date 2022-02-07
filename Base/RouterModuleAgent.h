#ifndef _BASE_ROUTER_MODULE_AGENT_H_
#define _BASE_ROUTER_MODULE_AGENT_H_

#include "TcpClient.h"
#include "RouterModuleBase.h"
#include "JYThread.h"
#include "LockQueue.h"

// .h
#define ROUTER_AGENT_DEFINE(class_name) \
private:\
    void    ProcessNetwork(); \
    typedef void (class_name::* PROCESS_PROTOCOL_FUNC)(BYTE* pbyData, size_t uSize); \
    typedef std::vector<PROCESS_PROTOCOL_FUNC> RouterProtocolFuncVector; \
    typedef std::vector<int>                   RouterProtocolSizeVector; \
    RouterProtocolFuncVector                   m_ProcessProtocolFuns[ermt_end]; \
    RouterProtocolSizeVector                   m_ProcessProtocolSize[ermt_end]; \
    BYTE                                       m_byRecvBuffer[MAX_INTERNAL_NETWORK_PROTOCOL_SIZE]; \
    RouterModuleAgent                          m_Agent;


// .cpp
#define REGISTER_ROUTER_FUNC(eModuleType, ProtocolID, FuncName, ProtocolSize)  \
{ \
    while (m_ProcessProtocolFuns[eModuleType].size() <= ProtocolID) \
    { \
        m_ProcessProtocolFuns[eModuleType].push_back(NULL); \
        m_ProcessProtocolSize[eModuleType].push_back(0); \
    } \
    m_ProcessProtocolFuns[eModuleType][ProtocolID] = FuncName;                  \
    m_ProcessProtocolSize[eModuleType][ProtocolID] = ProtocolSize; \
}

#define ROUTER_AGENT_IMPLEMENT(class_name) \
void class_name::ProcessNetwork() \
{ \
    bool                  bRetCode    = false; \
    BYTE*                 pbyData     = NULL; \
    size_t                uDataLen    = 0; \
    RouterModuleType      eType       = ermt_begin; \
    uint16_t              nProtocolID = 0; \
    PROCESS_PROTOCOL_FUNC Func; \
 \
    while (true) \
    { \
        pbyData = m_byRecvBuffer; \
 \
        bRetCode = m_Agent.Recv(sizeof(m_byRecvBuffer), pbyData, &uDataLen, &eType, &nProtocolID); \
        JY_PROCESS_ERROR(bRetCode); \
        JYLOG_PROCESS_ERROR(nProtocolID < m_ProcessProtocolFuns[eType].size()); \
 \
        if (m_ProcessProtocolSize[eType][nProtocolID] != UNDEFINED_PROTOCOL_SIZE) \
        { \
            JYLOG_PROCESS_ERROR(m_ProcessProtocolSize[eType][nProtocolID] == uDataLen); \
        } \
 \
        Func = m_ProcessProtocolFuns[eType][nProtocolID]; \
        JYLOG_PROCESS_ERROR(Func); \
 \
        (this->*Func)(pbyData, uDataLen); \
    } \
 \
Exit0: \
    return; \
}

class RouterModuleAgent : public TcpClient
{
public:
    RouterModuleAgent();
    virtual ~RouterModuleAgent();

    bool Init(RouterModuleType eType);
    void UnInit();

    bool Recv(size_t uLimitSize, BYTE* &pbyData, size_t* puDataLen, RouterModuleType* peType, uint16_t* pnProtocolID);
    bool SendToModule(RouterModuleType eType, uint16_t nProtocolID, BYTE* pbyData, size_t uDataLen);

private:
    static void WorkThread(void* pvParam);
    void Run();
    void ProcessPackage(BYTE* pbyData, size_t uDataLen);
    void ConnectionLost();
    void SendFlush();

private:
    RouterModuleType m_eType;
    JYThread         m_Thread;
    LockQueue        m_RecvQueue; // agent received
    LockQueue        m_SendQueue;
    BYTE             m_byThreadBuffer[MAX_INTERNAL_NETWORK_PROTOCOL_SIZE];
    BYTE             m_byMainBuffer[MAX_INTERNAL_NETWORK_PROTOCOL_SIZE];
};

#endif