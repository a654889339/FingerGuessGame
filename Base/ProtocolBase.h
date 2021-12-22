#ifndef _BASE_PROTOCOL_BASE_H_
#define _BASE_PROTOCOL_BASE_H_

#define REGISTER_EXTERNAL_FUNC(ProtocolID, FuncName, ProtocolSize)  \
{m_ProcessProtocolFuns[ProtocolID] = FuncName;                  \
    m_nProtocolSize[ProtocolID] = ProtocolSize;}

#define UNDEFINED_PROTOCOL_SIZE -1

struct PROTOCOL_HEADER
{
    WORD wProtocolID;
};

#endif