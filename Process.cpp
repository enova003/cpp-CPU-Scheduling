#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>

#include "Process.h"

using namespace std;

// Function to read processes from file
void Process::readProcessesFromFile(queue<Process>& processes, const string& filename){
    ifstream infile(filename);
    string ignoreFirstLine; 
    if (!infile) {
        cerr << "Error opening file: " << filename << endl;
        exit(1);
    }

    int arrival, burst, priority;
    int pid = 1;
    getline(infile, ignoreFirstLine);  // Used to ignore the words in the input file
    while (infile >> arrival >> burst >> priority) {
        Process p(pid++, arrival, priority, burst);
        processes.push(p);
    }
    infile.close();
}

bool Process::compareArrivalTime(const Process& p1, const Process& p2){
    return p1.arrivalTime < p2.arrivalTime;
}

bool Process::compareBurstTime(const Process& p1, const Process& p2) {
    return p1.burstTime < p2.burstTime;
}

// Function to simulate FIFO scheduling
void Process::simulateFIFO(queue<Process>& processes, ofstream& myfile){
    int currentTime = 0;
    int totalProcesses = processes.size();
    vector<Process> completedProcesses;

    while (!processes.empty()) {
        Process current = processes.front();
        processes.pop();

        if (currentTime < current.arrivalTime)
            currentTime = current.arrivalTime;

        current.startTime = currentTime;
        current.completionTime = currentTime + current.burstTime;
        current.turnaroundTime = current.completionTime - current.arrivalTime;
        current.waitingTime = current.turnaroundTime - current.burstTime;
        current.responseTime = current.waitingTime;

        completedProcesses.push_back(current);
        currentTime = current.completionTime;
        
        if (completedProcesses.size() >= totalProcesses)
            break;
    }

    // Print statistics to console
    cout << "FIFO Scheduling Statistics:" << endl;
    cout << "Number of processes: " << totalProcesses << endl;
    cout << "Total elapsed time: " << currentTime << " units" << endl;
    cout << "Throughput: " << fixed << setprecision(2) << (double)totalProcesses / currentTime << " processes/unit time" << endl;
    // Print statistics to ouput file
    myfile << "FIFO Scheduling Statistics:" << endl;
    myfile << "Number of processes: " << totalProcesses << endl;
    myfile << "Total elapsed time: " << currentTime << " units" << endl;
    myfile << "Throughput: " << fixed << setprecision(2) << (double)totalProcesses / currentTime << " processes/unit time" << endl;

    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;
    int totalResponseTime = 0;

    for (const auto& p : completedProcesses) {
        totalWaitingTime += p.waitingTime;
        totalTurnaroundTime += p.turnaroundTime;
        totalResponseTime += p.responseTime;
    }

    //Print statistics to console
    cout << "Average waiting time: " << fixed << setprecision(2) << (double)totalWaitingTime / totalProcesses << " units" << endl;
    cout << "Average turnaround time: " << fixed << setprecision(2) << (double)totalTurnaroundTime / totalProcesses << " units" << endl;
    cout << "Average response time: " << fixed << setprecision(2) << (double)totalResponseTime / totalProcesses << " units" << endl;
    cout << endl;
    //Print statistics to output file
    myfile << "Average waiting time: " << fixed << setprecision(2) << (double)totalWaitingTime / totalProcesses << " units" << endl;
    myfile << "Average turnaround time: " << fixed << setprecision(2) << (double)totalTurnaroundTime / totalProcesses << " units" << endl;
    myfile << "Average response time: " << fixed << setprecision(2) << (double)totalResponseTime / totalProcesses << " units" << endl;
    myfile << endl;
}

// Function to simulate SJF scheduling without preemption
void Process::simulateSJF(queue<Process>& processes, ofstream& myfile){
    int currentTime = 0;
    int totalProcesses = processes.size();
    vector<Process> completedProcesses;

    // Priority queue to simulate SJF (using burst time as priority)
    priority_queue<Process, vector<Process>, decltype(&Process::compareBurstTime)> readyQueue(&Process::compareBurstTime);

    // Push all processes into the readyQueue (initially ordered by arrival time)
    while (!processes.empty()) {
        readyQueue.push(processes.front());
        processes.pop();
    }

    while (!readyQueue.empty()) {
        Process current = readyQueue.top();
        readyQueue.pop();

        if (currentTime < current.arrivalTime)
            currentTime = current.arrivalTime;

        current.startTime = currentTime;
        current.completionTime = currentTime + current.burstTime;
        current.turnaroundTime = current.completionTime - current.arrivalTime;
        current.waitingTime = current.turnaroundTime - current.burstTime;
        current.responseTime = current.waitingTime;

        completedProcesses.push_back(current);
        currentTime = current.completionTime;

        if (completedProcesses.size() >= totalProcesses)
            break;

        // Move processes from original queue to readyQueue if they have arrived by current time
        while (!processes.empty() && processes.front().arrivalTime <= currentTime) {
            readyQueue.push(processes.front());
            processes.pop();
        }
    }

    // Print statistics to console
    cout << "SJF Scheduling Statistics:" << endl;
    cout << "Number of processes: " << totalProcesses << endl;
    cout << "Total elapsed time: " << currentTime << " units" << endl;
    cout << "Throughput: " << fixed << setprecision(2) << (double)totalProcesses / currentTime << " processes/unit time" << endl;
    //Print statistics to output file
    myfile << "SJF Scheduling Statistics:" << endl;
    myfile << "Number of processes: " << totalProcesses << endl;
    myfile << "Total elapsed time: " << currentTime << " units" << endl;
    myfile << "Throughput: " << fixed << setprecision(2) << (double)totalProcesses / currentTime << " processes/unit time" << endl; 
    
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;
    int totalResponseTime = 0;

    for (const auto& p : completedProcesses) {
        totalWaitingTime += p.waitingTime;
        totalTurnaroundTime += p.turnaroundTime;
        totalResponseTime += p.responseTime;
    }

    // Print statistics to console
    cout << "Average waiting time: " << fixed << setprecision(2) << (double)totalWaitingTime / totalProcesses << " units" << endl;
    cout << "Average turnaround time: " << fixed << setprecision(2) << (double)totalTurnaroundTime / totalProcesses << " units" << endl;
    cout << "Average response time: " << fixed << setprecision(2) << (double)totalResponseTime / totalProcesses << " units" << endl;
    cout << endl;
    // Print statistics to output file
    myfile << "Average waiting time: " << fixed << setprecision(2) << (double)totalWaitingTime / totalProcesses << " units" << endl;
    myfile << "Average turnaround time: " << fixed << setprecision(2) << (double)totalTurnaroundTime / totalProcesses << " units" << endl;
    myfile << "Average response time: " << fixed << setprecision(2) << (double)totalResponseTime / totalProcesses << " units" << endl;
    myfile << endl;   
}

// Function to simulate Priority scheduling with preemption
void Process::simulatePriority(queue<Process>& processes, ofstream& myfile){
    int currentTime = 0;
    int totalProcesses = processes.size();
    vector<Process> completedProcesses;
    priority_queue<Process, vector<Process>, function<bool(Process, Process)>> readyQueue([](Process p1, Process p2) {
        return p1.priority > p2.priority; // Highest priority should come first
    });

    while (!processes.empty() || !readyQueue.empty()) {
        while (!processes.empty() && processes.front().arrivalTime <= currentTime) {
            readyQueue.push(processes.front());
            processes.pop();
        }

        if (!readyQueue.empty()) {
            Process current = readyQueue.top();
            readyQueue.pop();

            current.startTime = currentTime;
            current.completionTime = currentTime + current.burstTime;
            current.turnaroundTime = current.completionTime - current.arrivalTime;
            current.waitingTime = current.turnaroundTime - current.burstTime;
            current.responseTime = current.waitingTime;

            completedProcesses.push_back(current);
            currentTime = current.completionTime;
        } else {
            currentTime++;
        }

        if (completedProcesses.size() >= totalProcesses)
            break;
    }

    // Print statistics to console
    cout << "Priority Scheduling Statistics:" << endl;
    cout << "Number of processes: " << totalProcesses << endl;
    cout << "Total elapsed time: " << currentTime << " units" << endl;
    cout << "Throughput: " << fixed << setprecision(2) << (double)totalProcesses / currentTime << " processes/unit time" << endl;
    //Print statistics to output file
    myfile << "Priority Scheduling Statistics:" << endl;
    myfile << "Number of processes: " << totalProcesses << endl;
    myfile << "Total elapsed time: " << currentTime << " units" << endl;
    myfile << "Throughput: " << fixed << setprecision(2) << (double)totalProcesses / currentTime << " processes/unit time" << endl;   
    
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;
    int totalResponseTime = 0;

    for (const auto& p : completedProcesses) {
        totalWaitingTime += p.waitingTime;
        totalTurnaroundTime += p.turnaroundTime;
        totalResponseTime += p.responseTime;
    }

    //Print statistics to console
    cout << "Average waiting time: " << fixed << setprecision(2) << (double)totalWaitingTime / totalProcesses << " units" << endl;
    cout << "Average turnaround time: " << fixed << setprecision(2) << (double)totalTurnaroundTime / totalProcesses << " units" << endl;
    cout << "Average response time: " << fixed << setprecision(2) << (double)totalResponseTime / totalProcesses << " units" << endl;
    cout << endl;
    //Print statistics to output file
    myfile << "Average waiting time: " << fixed << setprecision(2) << (double)totalWaitingTime / totalProcesses << " units" << endl;
    myfile << "Average turnaround time: " << fixed << setprecision(2) << (double)totalTurnaroundTime / totalProcesses << " units" << endl;
    myfile << "Average response time: " << fixed << setprecision(2) << (double)totalResponseTime / totalProcesses << " units" << endl;
    myfile << endl;
}
