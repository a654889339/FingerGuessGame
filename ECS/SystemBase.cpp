#include "stdafx.h"
#include "SystemBase.h"

template <typename Component>
SystemBase<Component>::SystemBase()


template <typename Component>
bool SystemBase<Component>::RegisterUpdatePriorLevel(uint8_t uPriorLevel, PROCESS_UPDATE_FUNC Func)

template <typename Component>
bool SystemBase<Component>::SetComponentList(ComponentManager* pComponentList)

//////////////////////////////////////////////////////////////////////////

template <typename Component>
bool SystemBase<Component>::NeedUpdate(uint8_t uPriorLevel)


template <typename Component>
bool SystemBase<Component>::Update(uint8_t uPriorLevel)
