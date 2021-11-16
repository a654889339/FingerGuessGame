#ifndef _ECS_SYSTEM_OBJ_H_
#define _ECS_SYSTEM_OBJ_H_

#define ECS_SYSTEM_UPDATE_FUNC_COUNT 3

class SystemObj
{
public:
    virtual bool NeedUpdate(uint8_t uPriorLevel) = 0; // �ж�������ȼ��ĸ��º����Ƿ�ע���
    virtual bool Update(uint8_t uPriorLevel) = 0;

    bool IsEnable() { return m_bEnable; }
    void Enable() { m_bEnable = true; }
    void Disable() { m_bEnable = false; }

private:
    bool    m_bEnable;     // ϵͳ����
};

#endif