#include "game.h"

#include <stdlib.h>

#include "math.h"
#include "raylib.h"
#include "screen.h"

int random_in_range(int min, int max) {
    return min + (rand() % (max - min + 1));
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

bool exists_collision_with_boundary(snake* s) {
    Vector2 pos = s->head->position;
    return pos.x - 12 < 0 || pos.x + 12 > SCREEN_WIDTH || pos.y - 12 < 0 ||
           pos.y + 12 > SCREEN_HEIGHT;
}

bool exists_collision_with_self(snake* s) {
    if (s->length <= 10) return false;
    Vector2        snake_head_pos = s->head->position;
    snake_segment* tmp =
        s->head->next->next->next->next->next->next->next->next->next;
    static double collision_distance = 1;

    bool collision = false;
    for (int i = 0; i < s->length; i++) {
        if (collision == true || tmp == NULL) {
            break;
        }
        switch (s->direction) {
            case UP:
                collision =
                    (collision_distance >=
                     (fabs((snake_head_pos.y - 5) - (tmp->position.y + 5)))) &&
                    (snake_head_pos.x > tmp->position.x - 5 &&
                     snake_head_pos.x < tmp->position.x + 5);
                break;
            case DOWN:
                collision =
                    (collision_distance >=
                     (fabs((snake_head_pos.y + 5 - tmp->position.y - 5)))) &&
                    (snake_head_pos.x > tmp->position.x - 5 &&
                     snake_head_pos.x < tmp->position.x + 5);

                break;
            case LEFT:
                collision =
                    collision_distance >=
                        (fabs((snake_head_pos.x - 5 - tmp->position.x + 5))) &&

                    (snake_head_pos.y > tmp->position.y - 5 &&
                     snake_head_pos.y < tmp->position.y + 5);
                break;
            case RIGHT:
                collision =
                    collision_distance >=
                        (fabs((snake_head_pos.x + 5 - tmp->position.x - 5))) &&

                    (snake_head_pos.y > tmp->position.y - 5 &&
                     snake_head_pos.y < tmp->position.y + 5);
                break;
        }
        tmp = tmp->next;
    }
    return collision;
}
