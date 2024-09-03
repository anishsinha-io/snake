cmake_minimum_required(VERSION 3.10)

project(snake LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")

include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/lib)

file(GLOB SRCS src/*.c)
add_executable(snake main.c ${SRCS})
target_link_libraries(snake raylib "-framework CoreVideo" "-framework IOKit" "-framework Cocoa" "-framework GLUT" "-framework OpenGL")

add_executable(snake_test ${CMAKE_SOURCE_DIR}/test/main.c ${SRCS})
target_link_libraries(snake_test raylib cmocka "-framework CoreVideo" "-framework IOKit" "-framework Cocoa" "-framework GLUT" "-framework OpenGL")


add_custom_target(run
    COMMAND snake
    DEPENDS snake
    COMMENT "Running snake"
)

add_custom_target(run_test
    COMMAND snake_test
    DEPENDS snake_test
    COMMENT "Running tests"
)
