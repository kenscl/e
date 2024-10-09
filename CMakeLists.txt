cmake_minimum_required(VERSION 3.2)
project(e)

find_package(Curses REQUIRED)

include_directories(${CURSES_INCLUDE_DIR})

add_executable(e src/main.c src/screen.h src/screen.c src/file.h src/file.c)
target_link_libraries(e ${CURSES_LIBRARIES})
