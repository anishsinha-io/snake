#include "game.h"

#include <stdlib.h>

#include "math.h"
#include "raylib.h"
#include "screen.h"

int draw_apple(state* st) {
    if (st->apple_pos.x == -1 || st->apple_pos.y == -1) {
        st->apple_pos.x = rand() % SCREEN_WIDTH;
        st->apple_pos.y = rand() % SCREEN_HEIGHT;
    }

    DrawCircle(st->apple_pos.x, st->apple_pos.y, 10.0f, RED);
    return 0;
}

bool exists_collision_with_apple(state* st, snake* s) {
    Vector2 snake_head_pos = s->head->position;
    Vector2 apple_pos = st->apple_pos;

    // 22 instead of 25 because at high FPS it looks like the snake grabs the
    // apple early at 25, even though 25 is the mathematically correct distance
    static double collision_distance = 22;

    double distance = sqrt(pow((double)(snake_head_pos.x - apple_pos.x), 2.0) +
                           pow((double)(snake_head_pos.y - apple_pos.y), 2.0));

    return distance <= collision_distance;
}
