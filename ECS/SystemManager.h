#ifndef _ECS_SYSTEM_MANAGER_H_
#define _ECS_SYSTEM_MANAGER_H_

#include "SystemBase.h"

#include <vector>

class SystemManager
{
public:
    SystemManager();
    virtual ~SystemManager();

    bool Init();
    void UnInit();

    void Active();

    bool AddSystem(SystemBase* pSystem);

private:
    void UpdateAll();

    std::vector<SystemBase*> m_SystemList[ECS_SYSTEM_UPDATE_FUNC_COUNT];
    // Ϊʲô���ﲻ��һ��std::vector<SystemBase*> m_SystemList������һ�����飿
    // Update ���ֻ��ÿ��ϵͳ����һ�Σ��ǲ�����
    // �����е�ϵͳ����Ҫ��һ����ѵ��������Σ��������Ⱥ�˳�򣬱���Moveϵͳ��Ҫ��ս��ϵͳ��ʼǰ���ȶ�����Ԥ������ս��ϵͳ�������λ�÷����ͻ��ˡ�
    // ��Ȼ�����޷���֤MoveSystem��FightSystem˭��AddSystem���뱾class��Ҳ���޷���֤һ���򵥵�ÿ����ѵ��Move���ȡ�
    // ������Ƕ�Update���Ϊ��׶Ρ���������SystemBase ����Update Before, Update, Update After��������������ʵ���ɼ̳�SystemBase��ʵ�������Լ��ĺ���ʵ�֡�
    // MoveSystem��ʵ����Update Before������Ԥ������Update Afterλ�÷����ͻ��ˡ�FightSyste����Update��λ�ô���
    // ���ڲ�һ��ֻ��Update Before, Update, Update After��������, ������ECS_SYSTEM_UPDATE_FUNC_COUNT������������
    // ��ô m_SystemList[0] �ͱ�������ע����Update Before��System��

    // ���⣺������Update Before��System���޷���֤�Ⱥ���ù�ϵ��������ʱҪ����System��������
    // ���ƣ�System֮�����������һ��ͼ���Զ����ɣ�Ȼ���������

};

#endif