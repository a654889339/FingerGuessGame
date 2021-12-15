#include "stdafx.h"
#include "MoveSystem.h"

MoveSystem::MoveSystem()
{
    RegisterUpdatePriorLevel(0, SystemBase::Update0);
}

MoveSystem::~MoveSystem()
{

}
// 先将加速度和速度作用到(x,y,z) 上
// 再将加速度作用到速度上
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
}