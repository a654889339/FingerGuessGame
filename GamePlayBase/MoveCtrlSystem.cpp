#include "stdafx.h"
#include "MoveCtrlSystem.h"

MoveCtrlSystem::MoveCtrlSystem()
{
    RegisterUpdatePriorLevel(0, &SystemBase<MoveCtrlComponent>::Update0);
}

MoveCtrlSystem::~MoveCtrlSystem()
{

}

bool MoveCtrlSystem::Update0(MoveCtrlComponent* pComponent)
{
    return true;
}