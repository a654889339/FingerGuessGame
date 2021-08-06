#ifndef _CLIENT_WORLD_H_
#define _CLIENT_WORLD_H_

class ClientWorld
{
public:
    ClientWorld();
    virtual ~ClientWorld();

    bool Init();
    void UnInit();

private:
    bool LoadConfig();

    char m_szIP[_NAME_LEN];
    int  m_nPort;
};

#endif