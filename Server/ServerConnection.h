#ifndef _SERVER_CONNECTION_H_
#define _SERVER_CONNECTION_H_

class ServerConnection
{
public:
    ServerConnection();
    virtual ~ServerConnection();

    bool Init(const char szIP[], int nPort);
    void UnInit();

    void Active();
};

#endif