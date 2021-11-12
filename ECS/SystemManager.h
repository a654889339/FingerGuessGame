#ifndef _ECS_SYSTEM_MANAGER_H_
#define _ECS_SYSTEM_MANAGER_H_

#include "SystemBase.h"

#include <vector>

class SystemManager
{
public:
    SystemManager();
    virtual ~SystemManager();

    bool Init();
    void UnInit();

    void Active();

    bool AddSystem(SystemBase* pSystem);

private:
    void UpdateAll();

    std::vector<SystemBase*> m_SystemList[ECS_SYSTEM_UPDATE_FUNC_COUNT];
    // 为什么这里不是一个std::vector<SystemBase*> m_SystemList，而是一个数组？
    // Update 如果只是每个系统调用一次，是不够的
    // 比如有的系统，需要在一个轮训里调用两次，并且有先后顺序，比如Move系统需要在战斗系统开始前，先对输入预处理，在战斗系统结束后把位置发给客户端。
    // 显然我们无法保证MoveSystem和FightSystem谁先AddSystem进入本class，也就无法保证一个简单的每次轮训是Move优先。
    // 因此我们对Update拆分为多阶段。举例：在SystemBase 存在Update Before, Update, Update After三个函数，具体实现由继承SystemBase的实例决定自己的函数实现。
    // MoveSystem则实现在Update Before对输入预处理，在Update After位置发给客户端。FightSyste则在Update做位置处理。
    // 由于不一定只有Update Before, Update, Update After三个函数, 我们用ECS_SYSTEM_UPDATE_FUNC_COUNT来控制数量。
    // 那么 m_SystemList[0] 就保存所有注册了Update Before的System。

    // 额外：若都是Update Before的System，无法保证先后调用关系，因此设计时要考虑System的拓扑序。
    // 完善：System之间的拓扑序由一张图表自动生成，然后导入进来。

};

#endif