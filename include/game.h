#ifndef GAME_H
#define GAME_H

#include "snake.h"
#include "state.h"

int  random_in_range(int min, int max);
bool exists_collision_with_apple(state* st, snake* s);
bool exists_collision_with_self(snake* s);
bool exists_collision_with_boundary(snake* s);

#endif  // GAME_H
