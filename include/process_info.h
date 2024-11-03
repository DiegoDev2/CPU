#pragma once
#include <vector>
#include <string>

struct ProcessInfo {
    int pid;
    std::string name;
    float cpuUsage;
    unsigned long memoryUsage;
};

std::vector<ProcessInfo> getProcessList();
