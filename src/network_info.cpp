#include <stdio.h>
#include <stdlib.h>
#include "network_info.h"

void getNetworkUsage(unsigned long &bytesReceived, unsigned long &bytesSent) {
    FILE *fp;
    char buffer[128];

    // Usar netstat para obtener estadísticas de la red
    fp = popen("netstat -ib", "r");
    if (fp == nullptr) {
        bytesReceived = bytesSent = 0;
        return;
    }

    while (fgets(buffer, sizeof(buffer), fp) != nullptr) {
        // Procesa la salida de netstat para obtener bytes recibidos y enviados
        // Este código es un ejemplo simplificado
        // Debes adaptar la lógica según la salida real de netstat
        sscanf(buffer, "%*s %*s %lu %lu", &bytesReceived, &bytesSent);
    }

    pclose(fp);
}
