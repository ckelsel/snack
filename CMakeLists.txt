cmake_minimum_required(VERSION 3.5)

project(snack)

add_executable(snack source/snack.c source/score.c)

target_link_libraries(snack ncurses)
