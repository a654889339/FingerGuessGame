#ifndef _BASE_ROUTER_MODULE_AGENT_H_
#define _BASE_ROUTER_MODULE_AGENT_H_

#include "TcpClient.h"

class RouterModuleAgent : public TcpClient
{
public:
    RouterModuleAgent();
    virtual ~RouterModuleAgent();

    bool Init();
    void UnInit();


};

#endif