#ifndef _CLIENT_CONNECTION_H_
#define _CLIENT_CONNECTION_H_

#include "TcpClient.h"

class ClientConnection : public TcpClient
{
public:
    ClientConnection();
    virtual ~ClientConnection();

    bool Init();
    void UnInit();


};
#endif