#ifndef _GLOBAL_DEF_H_
#define _GLOBAL_DEF_H_

#define GAME_FRAME_PER_SECOND 16
#define _NAME_LEN 32
#define ERROR_ID 0

enum GameOperateCode
{
    egoc_rock = 0,
    egoc_scissors,
    egoc_paper,

    egoc_total
};

enum GameResultCode
{
    erc_invalid,
    erc_win,
    erc_lose,
    erc_draw,
};

#endif