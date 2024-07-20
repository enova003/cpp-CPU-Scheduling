#ifndef PROCESS_H
#define PROCESS_H

#include <queue>
#include <string>
#include <vector>
#include <fstream>

// Struct to hold process information
struct Process {
    int id;
    int arrivalTime;
    int priority;
    int burstTime;
    int startTime;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
    int responseTime;

    // Default constructor
    Process() {}

    // Constructor with parameters
    Process(int pid, int arrival, int prio, int burst)
        : id(pid), arrivalTime(arrival), priority(prio), burstTime(burst),
          startTime(-1), completionTime(-1), waitingTime(0),
          turnaroundTime(0), responseTime(0) {}

    // Function to read processes from file
    static void readProcessesFromFile(std::queue<Process>& processes, const std::string& filename);

    // Static comparison functions for sorting processes
    static bool compareArrivalTime(const Process& p1, const Process& p2);
    static bool compareBurstTime(const Process& p1, const Process& p2);

    // Static function to simulate FIFO scheduling
    static void simulateFIFO(std::queue<Process>& processes, std::ofstream& myfile);

    // Static function to simulate SJF scheduling
    static void simulateSJF(std::queue<Process>& processes, std::ofstream& myfile);

    // Static function to simulate Priority scheduling with preemption
    static void simulatePriority(std::queue<Process>& processes, std::ofstream& myfile);

};

#endif // PROCESS_H
