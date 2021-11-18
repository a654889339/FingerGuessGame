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

// ��ҵ�������Ҫ����ɶԼ��ٶȵļ�Ȩ������һ����վ���������ǰ��������nDir�����Ȩ���ٶȣ�
// ����һ����ǰ������һ��Ҳ��ǰ�����򲻵������ٶȣ���Ϊ��һ���Ѿ���Ȩ�˼��ٶȣ���

struct MoveComponent
{
    int  nX;
    int  nY;
    int  nZ;
    BYTE nDir;             // ��ҳ��� [0,256)
    BYTE nAccDirXY; // ���ٶȷ���
    int  nAccXY;
    BYTE nVelDirXY;     // �ٶȷ���
    int  nVelXY;
    int  nAccZ;   // ��ֱ������ٶ�
    int  nVelZ;       // ��ֱ�����ٶ�
    bool bGravity;         // �Ƿ�������Ӱ��
};

#pragma pack()


typedef ComponentList<MoveComponent> MoveComponentList;
#endif