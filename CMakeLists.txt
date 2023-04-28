cmake_minimum_required(VERSION 3.14)
project(timer-clock-chronometer)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(test)

set(SOURCE_FILES Timer.cpp Timer.h Clock.cpp Clock.h Chronometer.cpp Chronometer.h Display.cpp Display.h Chronometer.h)
add_executable(timer-clock-chronometer main.cpp)
add_library(core ${SOURCE_FILES})
target_link_libraries(timer-clock-chronometer core)

set(CURSES_NEED_NCURSES, TRUE)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIRS})
target_link_libraries(timer-clock-chronometer ${CURSES_LIBRARIES})