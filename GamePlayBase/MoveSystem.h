#ifndef _GAMESERVER_MOVE_SYSTEM_H_
#define _GAMESERVER_MOVE_SYSTEM_H_

#include "SystemBase.h"
#include "GamePlayECSConfig.h"

class MoveSystem : SystemBase
{
public:
    MoveSystem();
    virtual ~MoveSystem();

    void Update(int nUpdateTime);
    bool SetComponentList(MoveComponentList* pList);

private:
    MoveComponentList* m_pComponentList; // Systemû�����ݣ�����Ҫ��������һ�� ��ҪUpdate�����ݿ顣

};

#endif