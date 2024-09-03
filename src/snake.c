#include "snake.h"

snake_segment* snake_segment_new(Vector2 position) {
    snake_segment* s = malloc(sizeof(snake_segment));
    s->position = position;
    s->next = s->prev = NULL;
    return s;
}

int snake_prepend(snake* snake, snake_segment* segment) {
    if (snake->head == NULL) {
        return 1;
    }
    segment->next = snake->head;
    snake->head->prev = segment;
    snake->head = segment;
    snake->length += 1;
    return 0;
}

int snake_append(snake* snake, snake_segment* segment) {
    if (snake->head == NULL) {
        return 1;
    }
    segment->prev = snake->tail;
    snake->tail->next = segment;
    snake->tail = segment;
    snake->length += 1;

    return 0;
}

int snake_pop(snake* snake, snake_segment* buf) {
    if (snake->length < 2) {
        return 1;
    }
    snake_segment* tmp = snake->tail;

    snake->tail->prev->next = NULL;
    snake->length -= 1;

    if (snake->length == 1) {
        snake->tail = snake->head;
    }
    if (buf != NULL) {
        memcpy(buf, tmp, sizeof(snake_segment));
    }
    return 0;
}

int snake_pop_front(snake* snake, snake_segment* buf) {
    if (snake->length < 2) {
        return 1;
    }
    snake_segment* tmp = snake->head;
    snake->head->next->prev = NULL;
    snake->length -= 1;

    if (snake->length == 1) {
        snake->tail = snake->head;
    }
    if (buf != NULL) {
        memcpy(buf, tmp, sizeof(snake_segment));
    }
    return 0;
}

int snake_move(snake* s, direction dir) {
    Vector2        first = s->head->position;
    snake_segment* new_segment =
        snake_segment_new((Vector2){s->head->position.x, s->head->position.y});

    switch (dir) {
        case UP:
            new_segment->position.y -= 5;
            // new_segment->position.y = first.y - 10;
            s->direction = UP;
            break;
        case DOWN:
            new_segment->position.y += 5;
            // new_segment->position.y = first.y + 10;
            s->direction = DOWN;
            break;
        case LEFT:
            // new_segment->position.x = first.x - 10;
            new_segment->position.x -= 5;
            s->direction = LEFT;
            break;
        case RIGHT:
            // new_segment->position.x = first.x + 10;
            s->direction = RIGHT;
            new_segment->position.x += 5;
            break;
    };

    snake_prepend(s, new_segment);
    snake_pop(s, NULL);
    return 0;
}

int snake_grow(snake* s) {
    Vector2 last = s->tail->position;
    snake_segment* new = snake_segment_new((Vector2){0, 0});

    switch (s->direction) {
        case UP:
            new->position.y = last.y + 0;
            new->position.x = last.x;
            break;
        case DOWN:
            new->position.y = last.y - 0;
            new->position.x = last.x;
            break;
        case LEFT:
            new->position.x = last.x + 0;
            new->position.y = last.y;
            break;
        case RIGHT:
            new->position.x = last.x - 0;
            new->position.y = last.y;
            break;
    }

    snake_append(s, new);
    return 0;
}

snake* snake_new(Vector2 position) {
    snake*         s = malloc(sizeof(snake));
    snake_segment* head = snake_segment_new(position);

    s->head = head;
    s->tail = head;
    s->direction = RIGHT;
    s->velocity = 1;
    s->length = 1;
    s->segment_width = 15;

    return s;
}

void snake_destroy(snake* s) {
    while (s->head != NULL) {
        snake_segment* next = s->head->next;
        free(s->head);
        s->head = next;
    }
}
