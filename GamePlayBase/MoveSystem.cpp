#include "stdafx.h"
#include "MoveSystem.h"

MoveSystem::MoveSystem()
{
    RegisterUpdatePriorLevel(0, &SystemBase::Update0);
}

MoveSystem::~MoveSystem()
{

}
// �Ƚ����ٶȺ��ٶ����õ�(x,y,z) ��
// �ٽ����ٶ����õ��ٶ���
bool MoveSystem::Update0(MoveComponent* pComponent)
{

}