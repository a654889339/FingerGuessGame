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

// ����ֻ�޸��ٶȺ��ƶ�״̬����ͬ�ƶ�״̬�������ٶ�����
struct MoveCtrlComponent
{
    BYTE    bEnable;
    BYTE    nDir;             // ��ҳ��� [0,256)
    BYTE    nOp;
    BYTE    nDirection8;      // ���̵�8������
    int_eid nMoveComponentIndex; // ���ڲ���MoveComponent������
};

struct MoveComponent
{
    BYTE eMoveState;
    int  nX;
    int  nY;
    int  nZ;
    BYTE nDir;             // ��ҳ��� [0,256)
    int  nAccXY; // >= 0
    BYTE nAccDirXY; // ���ٶȷ���
    int  nVelXY; // >= 0
    BYTE nVelDirXY;     // �ٶȷ���
    int  nAccZ;   // ��ֱ������ٶ� ������
    int  nVelZ;       // ��ֱ�����ٶ� ������
    bool bGravity;         // �Ƿ�������Ӱ��
};

#pragma pack()

typedef ComponentList<MoveCtrlComponent> MoveCtrlComponentList;
typedef ComponentList<MoveComponent>     MoveComponentList;
#endif