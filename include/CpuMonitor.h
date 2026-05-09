#pragma once
#ifndef _CPUMONITOR_H
#define _CPUMONITOR_H

#include <string>
#include <cstdint>

// Structure pour les données générales du CPU
typedef struct cpu {
    float frequency;
    float frequencyMax;
    float usageCPU;
    float* usagePerCPU;
    short nbrCPU;
} cpu;

// Structure pour les valeurs de temps lues dans /proc/stat
typedef struct CpuTimes {
    long long user = 0;
    long long nice = 0;
    long long system = 0;
    long long idle = 0;
    long long iowait = 0;
    long long irq = 0;
    long long softirq = 0;
    long long steal = 0;
    long long guest = 0;
    long long guest_nice = 0;

    long long totalIdleTime() const {
        return idle + iowait;
    }

    long long totalTime() const {
        return user + nice + system + idle + iowait + irq + softirq + 
               steal + guest + guest_nice;
    }
} CpuTimes;

class CpuMonitor {
    private:
        CpuTimes previousTimes;
        CpuTimes currentTimes;

    protected:
        cpu CPU;
        std::string rawCPU;
        CpuTimes readCpuTimes(); 
        void updateTimes(); 
        uint64_t getSnap(std::string calc);

    public:
        CpuMonitor();
        ~CpuMonitor();

        // Fusion : on garde le nom de dev mais on ajoute le délai de abdelhadiait
        float getCpuUsage(int delayMs = 1000);
        
        float getCpuFreq();
        std::string getCpuInfo();
        bool update();
        float calcCpuUsage(int log, int updateInterval = 5e5);
};

#endif
