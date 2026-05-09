#pragma once
#ifndef _SYSMON_H
#define _SYSMON_H

#include "./CpuMonitor.h"
#include "./MemoryMonitor.h"
#include "./ProcessMonitor.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstring>
#include <vector>
#include <filesystem>

using namespace std;

enum options
{
    _NLOG = 1000
};

std::vector<std::string> getVector(std::istringstream &iss);
bool isNumber(std::string &string);

class SysMon : public CpuMonitor, public MemoryMonitor, public ProcessMonitor{
protected :
    int updateInterval;
    bool fullLog;
    
public:

    SysMon(int , bool fullLog=false);
    
    ~SysMon();

    int run(int limit=3);

    string exportAsText();

    string exportAsCSV();

    bool update();
    
    static string getTime();

    static string getInfo(string _file_path);

    static void log(ostream &);

};


#endif

