#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "game.h"
#include "raylib.h"
#include "screen.h"
#include "snake.h"
#include "state.h"

#define BABY_DOLL_PINK \
    CLITERAL(Color) { 248, 140, 174, 255 }

#define FASHION_GREEN \
    CLITERAL(Color) { 179, 210, 109, 255 }

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake");

    SetTargetFPS(60);

    state st = STATE_INIT;

    srand((unsigned int)time(NULL));

    Vector2 apple_pos = {random_in_range(50, SCREEN_WIDTH - 50),
                         random_in_range(50, SCREEN_HEIGHT - 50)};
    st.apple_pos = apple_pos;

    snake* s =
        snake_new((Vector2){(float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2});

    while (!WindowShouldClose()) {
        if (st.status != GAMEOVER && st.status != START) {
            if (IsKeyDown(KEY_RIGHT) && s->direction != RIGHT) {
                if (s->direction != LEFT) {
                    snake_move(s, RIGHT);
                }
            } else if (IsKeyDown(KEY_LEFT) && s->direction != LEFT) {
                if (s->direction != RIGHT) {
                    snake_move(s, LEFT);
                }
            } else if (IsKeyDown(KEY_UP) && s->direction != UP) {
                if (s->direction != DOWN) {
                    snake_move(s, UP);
                }
            } else if (IsKeyDown(KEY_DOWN) && s->direction != DOWN) {
                if (s->direction != UP) {
                    snake_move(s, DOWN);
                }
            } else if (IsKeyDown(KEY_P)) {
                st.status = PAUSED;
            } else if (IsKeyDown(KEY_R)) {
                st.status = RUNNING;
            }
        } else {
            if (IsKeyDown(KEY_SPACE)) {
                st.status = RUNNING;
                st.score = 0;
            }
        }

        if (exists_collision_with_apple(&st, s)) {
            st.apple_pos =
                (Vector2){rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT};
            snake_grow(s);
            st.score += 1;

            int x = random_in_range(50, SCREEN_WIDTH - 50);
            int y = random_in_range(50, SCREEN_HEIGHT - 50);
            st.apple_pos.x = x;
            st.apple_pos.y = y;
        }

        if (exists_collision_with_self(s) ||
            exists_collision_with_boundary(s)) {
            st.status = GAMEOVER;
            snake_destroy(s);

            s = snake_new(
                (Vector2){(float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2});
        }

        if (st.status == RUNNING) {
            snake_move(s, s->direction);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Move the snake with arrow keys", 10, 10, 20, DARKGRAY);
        char score_msg[40];
        snprintf(score_msg, 40, "Score: %d", st.score);
        DrawText(score_msg, SCREEN_WIDTH - 100, 10, 20, DARKGRAY);

        snake_segment* tmp = s->head;

        for (int i = 0; i < s->length; i++) {
            DrawCircle(tmp->position.x, tmp->position.y, s->segment_width,
                       BABY_DOLL_PINK);
            tmp = tmp->next;
        }

        DrawCircle(st.apple_pos.x, st.apple_pos.y, 10.0f, FASHION_GREEN);

        if (st.status == PAUSED) {
            DrawText("Paused\n", SCREEN_WIDTH / 2 - 80, SCREEN_HEIGHT / 2 - 40,
                     40, DARKGRAY);
            DrawText("Press r to resume", SCREEN_WIDTH / 2 - 100,
                     SCREEN_HEIGHT / 2 + 10, 20, DARKGRAY);
        }

        if (st.status == GAMEOVER) {
            DrawText("Game Over!\n", SCREEN_WIDTH / 2 - 100,
                     SCREEN_HEIGHT / 2 - 40, 40, DARKGRAY);
            DrawText("Press space to play again", SCREEN_WIDTH / 2 - 120,
                     SCREEN_HEIGHT / 2 + 10, 20, DARKGRAY);
        }

        if (st.status == START) {
            DrawText("Snake!\n", SCREEN_WIDTH / 2 - 70, SCREEN_HEIGHT / 2 - 40,
                     40, DARKGRAY);
            DrawText("Press space to start", SCREEN_WIDTH / 2 - 110,
                     SCREEN_HEIGHT / 2 + 10, 20, DARKGRAY);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
