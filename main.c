#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "game.h"
#include "raylib.h"
#include "snake.h"
#include "state.h"

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Snake");

    SetTargetFPS(60);

    state st = STATE_INIT;

    srand((unsigned int)time(NULL));

    Vector2 apple_pos = {rand() % screenWidth, rand() % screenHeight};
    st.apple_pos = apple_pos;

    snake* s =
        snake_new((Vector2){(float)screenWidth / 2, (float)screenHeight / 2});

    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_RIGHT) && s->direction != RIGHT) {
            snake_move(s, RIGHT);
        } else if (IsKeyDown(KEY_LEFT) && s->direction != LEFT) {
            snake_move(s, LEFT);
        } else if (IsKeyDown(KEY_UP) && s->direction != UP) {
            snake_move(s, UP);
        } else if (IsKeyDown(KEY_DOWN) && s->direction != DOWN) {
            snake_move(s, DOWN);
        } else if (IsKeyDown(KEY_P)) {
            if (st.status == PAUSED) {
                st.status = RUNNING;
            } else {
                st.status = PAUSED;
            }
        }

        if (exists_collision_with_apple(&st, s)) {
            st.apple_pos =
                (Vector2){rand() % screenWidth, rand() % screenHeight};
            snake_grow(s);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Move the snake with arrow keys", 10, 10, 20, DARKGRAY);

        snake_segment* tmp = s->head;

        for (int i = 0; i < s->length; i++) {
            DrawCircle(tmp->position.x, tmp->position.y, s->segment_width,
                       PINK);
            tmp = tmp->next;
        }
        // while (tmp != NULL) {
        //     DrawCircle(tmp->position.x, tmp->position.y, s->segment_width,
        //                PINK);
        //     tmp = tmp->next;
        // }

        if (st.status == RUNNING) {
            snake_move(s, s->direction);
        }

        draw_apple(&st);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
