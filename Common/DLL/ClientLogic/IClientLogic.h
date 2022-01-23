#ifndef _ICLIENT_LOGIC_H_
#define _ICLIENT_LOGIC_H_

class IClientLogic
{
public:
    virtual bool Init() { return true; };
    virtual void UnInit() {};
    virtual bool PushE2C(BYTE* pbyData, size_t uDataLen) { return true; }
    virtual bool PopC2E(size_t uLimitSize, BYTE* pbyData, size_t* puDataLen) { return true; }
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
