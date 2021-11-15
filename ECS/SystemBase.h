#ifndef _ECS_SYSTEM_BASE_H_
#define _ECS_SYSTEM_BASE_H_

#define ECS_SYSTEM_UPDATE_FUNC_COUNT 3

class SystemBase
{
public:
    SystemBase() {m_bEnable = true; m_uUpdateFlag = 0;}

    virtual void Update(int nUpdateTime) = 0;

    bool IsEnable() {return m_bEnable;}
    void SetEnable(bool bEnableFlag) {m_bEnable = bEnableFlag;}

    bool IsUpdateTime(uint8_t uUpdateTime) { return (m_uUpdateFlag >> uUpdateTime) & 1; }
    void SetUpdateTime(bool bEnableFlag) {}

protected:
    bool    m_bEnable;
    uint8_t m_uUpdateFlag; // 表示Update1,2,3中哪几个是生效的
};

#endif