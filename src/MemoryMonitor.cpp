#include "../include/MemoryMonitor.h"
#include "../include/SysMon.h"
using namespace std;

// Constructeur
MemoryMonitor::MemoryMonitor() {
    // Initialisation des ressources si nécessaire
}


// Destructeur
MemoryMonitor::~MemoryMonitor() {
    // Libération des ressources si nécessaire

}

// Getting memory usage
size_t MemoryMonitor::memUsage(int logger)
{
    std::string info = SysMon::getInfo("/proc/meminfo");

    std::istringstream iss(info);
    std::string temp;
    std::vector<std::string> mem;
    while (iss >> temp)
    {
        mem.push_back(temp);
    }

    size_t memUsage = (stoi(mem[1]) - stoi(mem[4]));
    std::cout << "Free memory : " << mem[1] + mem[2] << " Available memory : " << mem[4] + mem[5] << " \x1b[41mMemory usage : " << memUsage << "kB\x1b[0m" << std::endl;
    if (logger == options::_NLOG)
    {
        std::stringstream out;

        out << "Free memory : " << mem[1] + mem[2] << " Available memory : " << mem[4] + mem[5] << " Memory usage : " << memUsage << "kB\n"
            << std::endl;
        SysMon::log(out);
    }
    return memUsage;
}

bool MemoryMonitor::update(){
    //To-Do
    memUsage(0);
    return true;
}

unsigned long long getUsedMemory() {
    ifstream meminfo("/proc/meminfo");
    if (!meminfo) {
        cout << "Impossible " << endl; 
        return 0.0;
    }

    string line;
    long mem_total = 0, mem_free = 0, buffers = 0, cached = 0;

    while (getline(meminfo, line)) {
        stringstream mo(line);
        string k;
        long valeur;
        string unite;

        // lire chaque ligne et extraire les données
        mo >> k >> valeur >> unite;

        if (k == "MemTotal:") {
            mem_total = valeur;
        } else if (k == "MemFree:") {
            mem_free = valeur;
        } else if (k == "Buffers:") {
            buffers = valeur;
        } else if (k == "Cached:") {
            cached = valeur;
        }

        //  pour arrêter la lecture
        if (mem_total && mem_free && buffers && cached) {
            break;
        }
    }

    // calculer la mémoire en Mo
    long used_memory = mem_total - mem_free - buffers - cached;
    return static_cast<float>(used_memory) / 1024; // Conversion en Mo
}
unsigned long long MemoryMonitor::getTotalMemory() const{
    return RAM.totalMemInMb;
}

unsigned long long MemoryMonitor::getUsedMemory() const{
    return RAM.usage;
}
