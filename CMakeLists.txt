cmake_minimum_required(VERSION 3.10)
project(task_manager_tui)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
include_directories(include)

add_executable(task_manager_tui
    src/main.cpp
    src/cpu_info.cpp
    src/memory_info.cpp
    src/network_info.cpp
    src/gpu_info.cpp
    src/process_info.cpp
    src/tui_display.cpp
)

target_link_libraries(task_manager_tui ${CURSES_LIBRARIES})
