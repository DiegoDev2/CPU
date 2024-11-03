#include "cpu_info.h"
#include "memory_info.h"
#include "network_info.h"
#include "gpu_info.h"
#include "process_info.h"
#include "tui_display.h"
#include <unistd.h>

int main(int argc, char **argv) {
    TUIDisplay display;
    display.init();

    while (true) {
        display.update();
        sleep(1);
    }

    display.cleanup();
    return 0;
}
