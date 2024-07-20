#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

#include "Process.h"

using namespace std;

int main(int argc, char* argv[]){
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input_filename>" << endl;
        return 1;
    }

    Process p;
    ofstream myfile;
    myfile.open("cpu-output-data.txt");

    queue<Process> processes;
    p.readProcessesFromFile(processes, argv[1]);

    // Copy of processes for each scheduler
    queue<Process> processesFIFO = processes;
    queue<Process> processesSJF = processes;
    queue<Process> processesPriority = processes;

    // Sort processes by arrival time for SJF and Priority schedulers
    vector<Process> processesVector;
    while (!processes.empty()) {
        processesVector.push_back(processes.front());
        processes.pop();
    }

    sort(processesVector.begin(), processesVector.end(), Process::compareArrivalTime);

    // Run simulations
    p.simulateFIFO(processesFIFO, myfile);
    p.simulateSJF(processesSJF, myfile);
    p.simulatePriority(processesPriority, myfile);
    myfile.close();

    return 0;
}
