#include "../include/SysMon.h"
#include <unistd.h>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;
namespace utils {

    vector<string> lire_lignes(const string& p) {
        vector<string> lignes;
        ifstream fichier(p);// Ouvre le fichier
        if (!fichier.is_open()) return lignes;

        string ligne;
        while (getline(fichier, ligne)) {
            lignes.push_back(ligne);// ajoute chaque ligne lue au vecteur 'lignes'
        }

        return lignes;
    }

}

SysMon::SysMon(int updateInterval, bool fullLog): CpuMonitor(), MemoryMonitor(), ProcessMonitor(){
    this->updateInterval=updateInterval;
    this->fullLog=fullLog;
}

SysMon::~SysMon(){}


int SysMon::run(int limit){
    int i = 0;
    while (i < limit)
    {
        usleep(updateInterval);
        if(!fullLog){
            system("clear");
        }
        update();
        i++;
    }
    return 0;
}

bool SysMon::update(){
    CpuMonitor::update();
    ProcessMonitor::update();
    MemoryMonitor::update();
    return true;
}

//function to get the current time for loggin.
string SysMon::getTime()
{
    time_t timestamp;
    time(&timestamp);
    char* time = ctime(&timestamp);

    if (time[strlen(time) - 1] == '\n')
        time[strlen(time) - 1] = '\0';
    return time;
}

// //Fetching required files '/proc/stat/' and '/proc/meminfo'.
string SysMon::getInfo(string _file_path)
{
    string content;
    stringstream content_stream;

    fstream info(_file_path, ios::in);
    if (!info)
    {
        cerr << "There was an error opening the file" << endl;
        return " ";
    }
    content_stream << info.rdbuf();
    content = content_stream.str();
    info.close();
    return content;
}

void SysMon::log(ostream &out)
{
    fstream logFile("log.txt", ios::app);
    logFile << out.rdbuf();
    logFile.close();
}

std::vector<std::string> getVector(std::istringstream &iss)
{
    int i = 0;
    std::vector<std::string> info;
    std::string content;
    while (iss >> content && i < 13)
    {
        info.push_back(content);
        i++;
    }

    return info;
}

bool isNumber(std::string &string)
{
    bool isNumber = true;
    for (auto str : string)
    {
        if (!std::isdigit(str))
        {
            isNumber = false;
            break;
        }
    }
    return isNumber;
}