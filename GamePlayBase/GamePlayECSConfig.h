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

// 玩家的输入需要处理成对加速度的加权。若上一次是站立，这次是前进，则往nDir方向加权加速度；
// 若上一次是前进，这一次也是前进，则不调整加速度（因为上一次已经加权了加速度）。

struct MoveComponent
{
    int  nX;
    int  nY;
    int  nZ;
    BYTE nDir;             // 玩家朝向 [0,256)
    BYTE nAccDirXY; // 加速度方向
    int  nAccXY;
    BYTE nVelDirXY;     // 速度方向
    int  nVelXY;
    int  nAccZ;   // 垂直方向加速度
    int  nVelZ;       // 垂直方向速度
    bool bGravity;         // 是否受重力影响
};

#pragma pack()


typedef ComponentList<MoveComponent> MoveComponentList;
#endif