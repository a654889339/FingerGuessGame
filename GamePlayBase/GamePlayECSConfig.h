#ifndef _GAMEPLAY_BASE_ECS_CONFIG_H_
#define _GAMEPLAY_BASE_ECS_CONFIG_H_

#include <ComponentList.h>

enum ComponentType
{
    ect_begin = 0,

    ect_move,
    ect_fight,

    ect_end
};


#pragma pack(1)

struct MoveComponent
{
    int nX;
    int nY;
    int nZ;
};

#pragma pack()


typedef ComponentList<MoveComponent> MoveComponentList;
#endif