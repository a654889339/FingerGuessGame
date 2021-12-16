#include "stdafx.h"
#include "MoveSystem.h"

MoveSystem::MoveSystem()
{
    RegisterUpdatePriorLevel(0, &SystemBase<MoveComponent>::Update0);
}

MoveSystem::~MoveSystem()
{

}
// �Ƚ����ٶȺ��ٶ����õ�(x,y,z) ��
// �ٽ����ٶ����õ��ٶ���
bool MoveSystem::Update0(MoveComponent* pComponent)
{
    if (pComponent->nAccXY)
    {
        pComponent->nAccDirXY = 0;
    }

    if (pComponent->nAccZ)
    {
        pComponent->nAccZ = 0;
    }
    return true;
}