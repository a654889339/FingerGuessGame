#ifndef _ECS_SYSTEM_OBJ_H_
#define _ECS_SYSTEM_OBJ_H_

#define ECS_SYSTEM_UPDATE_FUNC_COUNT 3

class SystemObj
{
public:
    virtual bool NeedUpdate(uint8_t uPriorLevel) = 0; // 判断这个优先级的更新函数是否注册过
    virtual bool Update(uint8_t uPriorLevel) = 0;

    bool IsEnable() { return m_bEnable; }
    void Enable() { m_bEnable = true; }
    void Disable() { m_bEnable = false; }

private:
    bool    m_bEnable;     // 系统开关
};

#endif