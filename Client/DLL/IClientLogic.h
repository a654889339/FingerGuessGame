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

#ifdef __cplusplus
extern "C"
{
#endif
    CLIENT_LOGIC_DLL_API IClientLogic* CreateClientLogic();
    CLIENT_LOGIC_DLL_API void DestroyClientLogic(IClientLogic* pClientLogic);
#ifdef __cplusplus
}
#endif

#endif
