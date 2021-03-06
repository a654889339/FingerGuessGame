#ifndef _BASE_PROTOCOL_BASE_H_
#define _BASE_PROTOCOL_BASE_H_

#define REGISTER_EXTERNAL_FUNC(ProtocolID, FuncName, ProtocolSize)  \
{m_ProcessProtocolFuns[ProtocolID] = FuncName;                  \
    m_nProtocolSize[ProtocolID] = ProtocolSize;}

#define UNDEFINED_PROTOCOL_SIZE -1
#define MAX_INTERNAL_NETWORK_PROTOCOL_SIZE 9056
#define MAX_IP_STRING_LEN 32

struct PROTOCOL_HEADER
{
    WORD wProtocolID;
};

#endif