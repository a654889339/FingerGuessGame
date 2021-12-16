#ifndef _SERVER_CONNECTION_SYSTEM_H_
#define _SERVER_CONNECTION_SYSTEM_H_

#include "ServerECSConfig.h"
#include "SystemBase.h"

class ConnectionSystem : public SystemBase<ConnectionComponent>
{
public:
    ConnectionSystem();
    virtual ~ConnectionSystem();

    bool Update(ConnectionComponent* pComponent);
};


#endif