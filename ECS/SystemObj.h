#ifndef _ECS_SYSTEM_OBJ_H_
#define _ECS_SYSTEM_OBJ_H_

class SystemObj
{
public:
    SystemObj() {m_bEnable = true;}
    bool IsEnable() { return m_bEnable; }
    void Enable() { m_bEnable = true; }
    void Disable() { m_bEnable = false; }

    virtual void Active() = 0;

private:
    bool    m_bEnable;
};

#endif