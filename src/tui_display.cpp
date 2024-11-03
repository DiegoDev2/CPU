// tui_display.cpp
#include <ncurses.h>
#include "tui_display.h"
#include "cpu_info.h"
#include "memory_info.h"
#include "network_info.h"
#include "gpu_info.h"
#include "process_info.h"

void TUIDisplay::init() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);
}

void TUIDisplay::update() {
    clear();
    unsigned long system, user, nice, idle;
    getCpuUsage(system, user, nice, idle);
    mvprintw(1, 1, "CPU Usage: %.2f%%", (float)(system + user + nice) / (system + user + nice + idle) * 100);

    unsigned long total, used, free;
    getMemoryUsage(total, used, free);
    mvprintw(2, 1, "Memory: %lu / %lu MB", used, total);

    refresh();
}

void TUIDisplay::cleanup() {
    endwin();
}
