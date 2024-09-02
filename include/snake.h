#ifndef SNAKE_H
#define SNAKE_H

#include <stdlib.h>
#include <string.h>

#include "raylib.h"

typedef enum direction { UP, DOWN, LEFT, RIGHT } direction;

typedef struct snake_segment {
    Vector2               position;
    struct snake_segment* next;
    struct snake_segment* prev;
} snake_segment;

typedef struct snake {
    unsigned int   segment_width;
    unsigned int   length;
    direction      direction;
    int            velocity;
    snake_segment* head;
    snake_segment* tail;
} snake;

snake_segment* snake_segment_new(Vector2 position);
snake*         snake_new(Vector2 position);
int            snake_prepend(snake* snake, snake_segment* segment);
int            snake_append(snake* snake, snake_segment* segment);
int            snake_pop(snake* snake, snake_segment* segment);
int            snake_pop_front(snake* snake, snake_segment* segment);
int            snake_move(snake* s, direction dir);
int            snake_grow(snake* s);
void           snake_destroy(snake* s);

#endif  // SNAKE_H
