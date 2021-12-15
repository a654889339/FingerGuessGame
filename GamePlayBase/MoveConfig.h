#ifndef _GAMEPLAYER_BASE_MOVE_CONFIG_H_
#define _GAMEPLAYER_BASE_MOVE_CONFIG_H_

// Ò»Ã×=16¸ñ

#define MOVE_DISTANCE_PER_SECOND 64
#define MOVE_DISTANCE_PER_FRAME  4

enum EMoveState
{
    ems_stand,
    ems_step,
    ems_run,
    ems_swim,

    ems_total,
};

const int szMoveSpeedLimit[ems_total] = 
{
    0,          // stand
    16,         // step
    48,         // run
    10,         // swim
};

#endif