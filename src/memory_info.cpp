#include <mach/mach.h>
#include "memory_info.h"

void getMemoryUsage(unsigned long &total, unsigned long &used, unsigned long &free) {
    mach_msg_type_number_t count = TASK_BASIC_INFO_COUNT;
    task_basic_info_data_t info;
    kern_return_t result = task_info(mach_task_self(), TASK_BASIC_INFO, (task_info_t)&info, &count);
    
    if (result == KERN_SUCCESS) {
        total = info.virtual_size / (1024 * 1024); 
        used = (info.resident_size / (1024 * 1024)); 
        free = total - used;
    } else {
        total = used = free = 0; 
    }
}
