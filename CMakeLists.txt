cmake_minimum_required(VERSION 3.14)
project(ElaboratoTimer)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(test)

set(SOURCE_FILES Timer.cpp Timer.h Clock.cpp Clock.h Chronometer.cpp Chronometer.h Display.cpp Display.h)
add_executable(ElaboratoTimer main.cpp)
add_library(core ${SOURCE_FILES})
target_link_libraries(ElaboratoTimer core)

set(CURSES_NEED_NCURSES, TRUE)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIRS})
target_link_libraries(ElaboratoTimer ${CURSES_LIBRARIES})