#ifndef _GAME_CENTER_H_
#define _GAME_CENTER_H_

#include "RouterGameCenterAgent.h"

class GameCenter
{
public:
    GameCenter();
    virtual ~GameCenter();

    bool Init();
    void UnInit();

    void Run();
    void Quit();

private:
    RouterGameCenterAgent m_RouterAgent;
};

extern GameCenter* g_pGameCenter;

#endif