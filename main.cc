#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mach/mach.h>

int getCpuInfo(unsigned long * pulSystem, unsigned long * pulUser, unsigned long * pulNice, unsigned long * pulIdle);
int main(int nn, char ** args) {
        if(nn<2)
        {
                printf("Please specify waiting time in seconds\n");
                return -1;
        }
        int nWaitSec = atoi(args[1]);
        if(nWaitSec<=0)
        {
                printf("Waiting interval in seconds should be positive integer\n");
                return -1;
        }
        unsigned long ulSystemPrevious;
        unsigned long ulUserPrevious;
        unsigned long ulNicePrevious;
        unsigned long ulIdlePrevious;
        int nErr = getCpuInfo(&ulSystemPrevious, &ulUserPrevious, &ulNicePrevious, &ulIdlePrevious);
        if(nErr != KERN_SUCCESS)
        {
                printf("Kernel error: %s\n", mach_error_string(nErr));
                return -1;
        }
        printf("Waiting for %d seconds\n", nWaitSec);
        sleep(nWaitSec);
        unsigned long ulSystemNext;
        unsigned long ulUserNext;
        unsigned long ulNiceNext;
        unsigned long ulIdleNext;
        nErr = getCpuInfo(&ulSystemNext, &ulUserNext, &ulNiceNext, &ulIdleNext);
        if(nErr != KERN_SUCCESS)
        {
                printf("Kernel error: %s\n", mach_error_string(nErr));
                return -1;
        }
        float fUsageTime = (float)(ulSystemNext - ulSystemPrevious) + (ulUserNext - ulUserPrevious) + (ulNiceNext - ulNicePrevious);
        float fTotalTime = fUsageTime + (float)(ulIdleNext - ulIdlePrevious);
        printf("Average CPU during last %d seconds is %f%%\n", nWaitSec, fUsageTime/fTotalTime*100);
        return 0;
}

int getCpuInfo(unsigned long * pulSystem, unsigned long * pulUser, unsigned long * pulNice, unsigned long * pulIdle)
{
        mach_msg_type_number_t  unCpuMsgCount = 0;
        processor_flavor_t nCpuFlavor = PROCESSOR_CPU_LOAD_INFO;;
        kern_return_t   nErr = 0;
        natural_t unCPUNum = 0;
        processor_cpu_load_info_t structCpuData;
        host_t host = mach_host_self();
        *pulSystem = 0;
        *pulUser = 0;
        *pulNice = 0;
        *pulIdle = 0;
        nErr = host_processor_info( host,nCpuFlavor,&unCPUNum,
                            (processor_info_array_t *)&structCpuData,&unCpuMsgCount );
        for(int i = 0; i<(int)unCPUNum; i++)
        {
                *pulSystem += structCpuData[i].cpu_ticks[CPU_STATE_SYSTEM];
                *pulUser += structCpuData[i].cpu_ticks[CPU_STATE_USER];
                *pulNice += structCpuData[i].cpu_ticks[CPU_STATE_NICE];
                *pulIdle += structCpuData[i].cpu_ticks[CPU_STATE_IDLE];
        }
        return nErr;
}
