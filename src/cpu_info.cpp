#include <mach/mach.h>
#include "cpu_info.h"

// Implementación de getCpuInfo
int getCpuInfo(unsigned long *pulSystem, unsigned long *pulUser, unsigned long *pulNice, unsigned long *pulIdle) {
    mach_msg_type_number_t unCpuMsgCount = 0;
    processor_flavor_t nCpuFlavor = PROCESSOR_CPU_LOAD_INFO;
    kern_return_t nErr = 0;
    natural_t unCPUNum = 0;
    processor_cpu_load_info_t structCpuData;
    host_t host = mach_host_self();

    *pulSystem = 0;
    *pulUser = 0;
    *pulNice = 0;
    *pulIdle = 0;

    nErr = host_processor_info(host, nCpuFlavor, &unCPUNum, (processor_info_array_t *)&structCpuData, &unCpuMsgCount);
    if (nErr != KERN_SUCCESS) {
        return nErr; // Retorna el error si hay uno
    }

    for (int i = 0; i < (int)unCPUNum; i++) {
        *pulSystem += structCpuData[i].cpu_ticks[CPU_STATE_SYSTEM];
        *pulUser += structCpuData[i].cpu_ticks[CPU_STATE_USER];
        *pulNice += structCpuData[i].cpu_ticks[CPU_STATE_NICE];
        *pulIdle += structCpuData[i].cpu_ticks[CPU_STATE_IDLE];
    }
    return KERN_SUCCESS; // Retorna éxito si todo va bien
}

// Implementación de getCpuUsage
void getCpuUsage(unsigned long &system, unsigned long &user, unsigned long &nice, unsigned long &idle) {
    unsigned long ulSystem, ulUser, ulNice, ulIdle;
    getCpuInfo(&ulSystem, &ulUser, &ulNice, &ulIdle);
    system = ulSystem;
    user = ulUser;
    nice = ulNice;
    idle = ulIdle;
}

