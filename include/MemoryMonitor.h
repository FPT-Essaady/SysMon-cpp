#pragma once
#ifndef _MEMORYMONITOR_H
#define _MEMORYMONITOR_H

#include <string>
#include <vector>

typedef struct ram{
    float usage;
    float freeMem;
    float usageSwp;
    float freeSwp;
    std::size_t totalMemInMb;
    std::size_t SwapMeminMb;
} ram;

class MemoryMonitor {
protected:
    ram RAM;
    std::vector<std::string> memInfo;

public:
    MemoryMonitor();
    
    ~MemoryMonitor();

    bool update();

    unsigned long long getTotalMemory() const;

    unsigned long long getFreeMemory() const;
    
    unsigned long long getUsedMemory() const;
    
    double getMemoryUsagePercentage() const;

    unsigned long long getTotalSwap() const;
    
    unsigned long long getFreeSwap() const;
    
    unsigned long long getUsedSwap() const;
    
    double getSwapUsagePercentage() const;

    std::size_t memUsage(int log);

};

#endif