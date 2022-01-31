#ifndef _ROUTER_MODULE_MGR_H_
#define _ROUTER_MODULE_MGR_H_

class RouterModuleMgr
{
public:
    RouterModuleMgr();
    virtual ~RouterModuleMgr();

    bool Init();
    void UnInit();


};

#endif