#ifndef _ICLIENT_LOGIC_H_
#define _ICLIENT_LOGIC_H_

class IClientLogic
{
public:
    virtual bool Init() { return true; };
    virtual void UnInit() {};

    virtual void Run() {};

};

#ifdef _CLIENT
#define CLIENT_LOGIC_DLL_API _declspec(dllexport)
#else
#define CLIENT_LOGIC_DLL_API _declspec(dllimport)
#endif

#endif
