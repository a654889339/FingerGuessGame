#ifndef _ECS_SYSTEM_BASE_H_
#define _ECS_SYSTEM_BASE_H_

class SystemBase
{
public:
    virtual void Update();
    virtual void Clear();
};

#endif