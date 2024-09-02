#ifndef GAME_H
#define GAME_H

#include "snake.h"
#include "state.h"

int  draw_apple(state* st);
bool exists_collision_with_apple(state* st, snake* s);

#endif  // GAME_H
