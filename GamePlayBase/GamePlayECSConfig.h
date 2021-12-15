#ifndef _GAMEPLAY_BASE_ECS_CONFIG_H_
#define _GAMEPLAY_BASE_ECS_CONFIG_H_

#include "CodeStd.h"
#include <ComponentList.h>

enum ComponentType
{
    ect_begin = 0,

    ect_move,
    ect_fight,

    ect_end
};

#pragma pack(1)

// 按键只修改速度和移动状态，不同移动状态有他的速度上限
struct MoveCtrlComponent
{
    BYTE    bEnable;
    BYTE    nDir;             // 玩家朝向 [0,256)
    BYTE    nOp;
    BYTE    nDirection8;      // 键盘的8个方向
    int_eid nMoveComponentIndex; // 用于查找MoveComponent的索引
};

struct MoveComponent
{
    BYTE eMoveState;
    int  nX;
    int  nY;
    int  nZ;
    BYTE nDir;             // 玩家朝向 [0,256)
    int  nAccXY; // >= 0
    BYTE nAccDirXY; // 加速度方向
    int  nVelXY; // >= 0
    BYTE nVelDirXY;     // 速度方向
    int  nAccZ;   // 垂直方向加速度 有正负
    int  nVelZ;       // 垂直方向速度 有正负
    bool bGravity;         // 是否受重力影响
};

#pragma pack()

typedef ComponentList<MoveCtrlComponent> MoveCtrlComponentList;
typedef ComponentList<MoveComponent>     MoveComponentList;
#endif