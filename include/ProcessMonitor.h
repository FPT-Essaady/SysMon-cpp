#pragma once
#ifndef _PROCESSMONITOR_H
#define _PROCESSMONITOR_H

#include <vector>
#include <string>
#include <sstream>

typedef struct ap{
    float cpu;
    float memory;
    struct time;
    std::string user;
    std::string pathName;
} activeProcesses;



class ProcessMonitor{
protected:
    activeProcesses AP;
    int nbrProcess;

public:
    
    ProcessMonitor();

    ~ProcessMonitor();

    bool update();

    activeProcesses getProcess(int);
    
    std::string getProcessInfo();

    std::string getProcessRaw();

};

#endif