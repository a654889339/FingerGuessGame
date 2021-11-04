#ifndef _ECS_COMPONENT_TYPE_H_
#define _ECS_COMPONENT_TYPE_H_

enum ComponentType
{
    ect_begin = 0,

    ect_move,
    ect_fight,

    ect_end
};

struct MoveComponent
{
    int nControl;
    int nX, nY;
    int nSpeed;
    int nFace;
};

struct FightComponent
{
    int nControl;
    int nX, nY;
    int nSpeed;
    int nFace;
};

#endif