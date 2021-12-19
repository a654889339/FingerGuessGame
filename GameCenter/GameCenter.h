#ifndef _GAME_CENTER_H_
#define _GAME_CENTER_H_

class GameCenter
{
public:
    GameCenter();
    virtual ~GameCenter();

    bool Init();
    void UnInit();

    void Run();
    void Quit();
};

extern GameCenter* g_pGameCenter;

#endif