#include <stdio.h>

#include "assert.h"
#include "cmocka.h"
#include "raylib.h"
#include "snake.h"

typedef struct {
    snake* snake;
} test_snake_fixture;

static int snake_tests_setup(void** state) {
    test_snake_fixture* snake_fixture = malloc(sizeof(test_snake_fixture));
    snake*              s = snake_new((Vector2){1, 1});
    assert(s->head != NULL);
    snake_fixture->snake = s;
    state[0] = snake_fixture;
    return 0;
}

static int snake_tests_teardown(void** state) {
    snake* s = ((test_snake_fixture*)(state[0]))->snake;
    snake_destroy(s);
    return 0;
}

static void test_snake_init_state(void** state) {
    snake* s = ((test_snake_fixture*)(state[0]))->snake;
    assert_non_null(s);
    assert_non_null(s->head);
    assert_true(s->direction == RIGHT);
    assert(s->length == 1);
    assert(s->head->position.x = 1);
}

static void test_snake_append_pop(void** state) {
    snake* s = ((test_snake_fixture*)(state[0]))->snake;

    assert(s->head->position.x == 1 && s->head->position.y == 1);
    assert(s->tail->position.x == 1 && s->tail->position.y == 1);

    int status = snake_append(s, snake_segment_new((Vector2){1, 2}));
    assert(status == 0);
    assert(s->length == 2);
    assert(s->tail->next == NULL);

    status = snake_append(s, snake_segment_new((Vector2){1, 3}));
    assert(s->tail->position.x == 1 && s->tail->position.y == 3);
    assert(s->length == 3);

    status = snake_append(s, snake_segment_new((Vector2){1, 4}));
    assert(s->tail->position.x == 1 && s->tail->position.y == 4);
    assert(s->length == 4);

    snake_segment buf;

    status = snake_pop(s, &buf);
    assert(buf.position.y = 4);
    assert(s->length == 3);

    status = snake_pop(s, &buf);
    assert(buf.position.y = 3);
    assert(s->length == 2);

    status = snake_pop(s, &buf);
    assert(buf.position.y = 2);
    assert(s->length == 1);

    status = snake_pop(s, &buf);
    assert(status == 1);
}

static void test_snake_prepend_pop_front(void** state) {
    snake* s = ((test_snake_fixture*)(state[0]))->snake;

    assert(s->head->position.x == 1 && s->head->position.y == 1);
    assert(s->tail->position.x == 1 && s->tail->position.y == 1);

    int status = snake_prepend(s, snake_segment_new((Vector2){1, 2}));
    assert(status == 0);
    assert(s->length == 2);

    status = snake_prepend(s, snake_segment_new((Vector2){1, 3}));
    assert(s->head->position.x == 1 && s->head->position.y == 3);
    assert(s->length == 3);

    status = snake_prepend(s, snake_segment_new((Vector2){1, 4}));
    assert(s->head->position.x == 1 && s->head->position.y == 4);
    assert(s->length == 4);

    snake_segment buf;

    status = snake_pop_front(s, &buf);
    assert(buf.position.y = 4);
    assert(s->length == 3);

    status = snake_pop_front(s, &buf);
    assert(buf.position.y = 3);
    assert(s->length == 2);

    status = snake_pop_front(s, &buf);
    assert(buf.position.y = 2);
    assert(s->length == 1);

    status = snake_pop_front(s, &buf);
    assert(status == 1);
}

int main(void) {
    const struct CMUnitTest snake_tests[] = {
        cmocka_unit_test(test_snake_init_state),
        cmocka_unit_test(test_snake_append_pop),
        cmocka_unit_test(test_snake_prepend_pop_front),
    };

    cmocka_run_group_tests(snake_tests, snake_tests_setup,
                           snake_tests_teardown);

    return 0;
}
