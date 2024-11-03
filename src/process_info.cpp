#include <dirent.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "process_info.h"

std::vector<ProcessInfo> getProcessList() {
    std::vector<ProcessInfo> processes;
    DIR *dir;
    struct dirent *entry;

    if ((dir = opendir("/proc")) == nullptr) {
        return processes; // Devuelve vacío si no se puede abrir /proc
    }

    while ((entry = readdir(dir)) != nullptr) {
        if (isdigit(entry->d_name[0])) { // Solo directorios de procesos
            ProcessInfo proc;
            proc.pid = atoi(entry->d_name);

            // Aquí leeríamos el nombre del proceso y el uso de recursos
            std::ifstream ifs("/proc/" + std::string(entry->d_name) + "/stat");
            if (ifs.is_open()) {
                std::string line;
                std::getline(ifs, line);
                std::istringstream iss(line);
                // Asumiendo que la estructura es conocida
                iss >> proc.pid >> proc.name; // Simplificado para obtener el nombre
                // Obtener el uso de CPU y memoria aquí...
            }
            processes.push_back(proc);
        }
    }
    closedir(dir);
    return processes;
}
