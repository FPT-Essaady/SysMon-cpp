#include "../include/CpuMonitor.h"
#include "../include/SysMon.h"
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>
#include <vector>
#include <iostream>
#include <unistd.h>

using namespace std;

// Constructeur
CpuMonitor::CpuMonitor() {
    CPU.frequencyMax = 0; 
    CPU.nbrCPU = 0; 
    // Initialisation du premier snapshot pour éviter un calcul erroné au premier appel
    previousTimes = readCpuTimes();
}

// Destructeur
CpuMonitor::~CpuMonitor() {
    // Libération des ressources si nécessaire
}

// Implémentation de la lecture de /proc/stat (provenant de dev/abdelhadiait)
CpuTimes CpuMonitor::readCpuTimes() {
    std::ifstream file("/proc/stat");
    std::string line;
    CpuTimes times = {};

    if (file.is_open()) {
        std::getline(file, line);
        std::istringstream iss(line);
        std::string label;
        iss >> label; // Ignore le mot "cpu"
        iss >> times.user >> times.nice >> times.system >> times.idle
            >> times.iowait >> times.irq >> times.softirq >> times.steal
            >> times.guest >> times.guest_nice;
    }
    return times;
}

// Méthode principale demandée par abdelhadiait
float CpuMonitor::getCpuUsage(int delayMs) {
    CpuTimes t1 = readCpuTimes();
    std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
    CpuTimes t2 = readCpuTimes();

    unsigned long long totalDiff = t2.totalTime() - t1.totalTime();
    unsigned long long idleDiff = t2.totalIdleTime() - t1.totalIdleTime();

    if (totalDiff == 0) return 0.0f;
    return 100.0f * (1.0f - (float)idleDiff / totalDiff);
}

bool CpuMonitor::update() {
    // Met à jour les données de la structure CPU
    CPU.usageCPU = getCpuUsage(100); // Utilise un petit délai pour l'update
    CPU.frequency = getCpuFreq(); 
    rawCPU = getCpuInfo();
    return true;
}

float CpuMonitor::getCpuFreq() {
    // À implémenter (lecture de /proc/cpuinfo ou scaling_cur_freq)
    return 0.0;
}

std::string CpuMonitor::getCpuInfo() {
    return SysMon::getInfo("/proc/cpuinfo");
}

// Méthode de calcul spécifique à la branche dev
float CpuMonitor::calcCpuUsage(int logger, int updateInterval) {
    CpuTimes t1 = readCpuTimes();
    usleep(updateInterval);
    CpuTimes t2 = readCpuTimes();

    unsigned long long totalDiff = t2.totalTime() - t1.totalTime();
    unsigned long long idleDiff = t2.totalIdleTime() - t1.totalIdleTime();

    float results = (totalDiff > 0) ? 100.0f * (1.0f - (float)idleDiff / totalDiff) : 0.0f;

    std::cout << "CpuUsage: \x1b[41m" << results << "%\n\x1b[0m";

    if (logger == 0) { // Remplacez par options::_NLOG si défini
        std::stringstream out;
        out << "UsedDiff: " << (totalDiff - idleDiff) << " TotalDiff: " << totalDiff << " Usage: " << results << "%\n";
        // SysMon::log(out); // Décommentez si SysMon::log est prêt
    }
    return results;
}