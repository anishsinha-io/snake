#ifndef STATE_H
#define STATE_H

#include "raylib.h"

typedef enum game_current_status {
    START,
    RUNNING,
    PAUSED,
    GAMEOVER,
} game_current_status;

typedef struct state {
    Vector2             apple_pos;
    game_current_status status;
    int                 score;
} state;

#define STATE_INIT {{-1, -1}, START, 0};

#endif
