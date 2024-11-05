#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <queue>

using namespace std;

struct Process {
    int id;
    int cpuBurst;     
    int ioBurst;      
    int waitingTime;  
    bool isCompleted; 
};

const int MAX_PROCESSES = 100;         
Process processes[MAX_PROCESSES]; // Array to hold processes
queue<Process*> readyQueue;       // Queue for ready processes
int numProcesses;                 // Number of processes created

pthread_mutex_t queueLock = PTHREAD_MUTEX_INITIALIZER;

void* FCFS(void* arg) {
    int totalWaitingTime = 0;
    int completedProcesses = 0;


    while (completedProcesses < numProcesses) {
        pthread_mutex_lock(&queueLock);

        if (!readyQueue.empty()) {
            // Get the process at the front of the queue
            Process* currentProcess = readyQueue.front();
            readyQueue.pop(); // Remove from front of the queue

            // Waiting time for the current process
            if (currentProcess->waitingTime == 0) {
                currentProcess->waitingTime = totalWaitingTime;
            }

            // Simulate CPU burst completion
            cout << "Executing Process " << currentProcess->id 
                 << " with CPU burst time: " << currentProcess->cpuBurst 
                 << " ms and I/O burst time: " << currentProcess->ioBurst << " ms\n";

            // Update total waiting time for next process
            totalWaitingTime += currentProcess->cpuBurst;

            // Check if the process has already gone through I/O
            if (!currentProcess->isCompleted) {
                currentProcess->isCompleted = true;
                cout << "Process " << currentProcess->id << " completed CPU burst and moved to I/O queue.\n";
                readyQueue.push(currentProcess); // Return to back of queue for I/O simulation
            } else {
                // Process has completed all cycles
                cout << "Process " << currentProcess->id << " has completed all cycles and is terminated.\n";
                completedProcesses++;
            }
        }

        pthread_mutex_unlock(&queueLock);
    }

    // Calculates average waiting 
    double averageWaitingTime = static_cast<double>(totalWaitingTime) / numProcesses;
    cout << "Average waiting time: " << averageWaitingTime << " ms\n";

    return nullptr;
}

int main() {
    cout << "Enter the number of processes to create (max " << MAX_PROCESSES << "): ";
    cin >> numProcesses;
    if (numProcesses > MAX_PROCESSES) numProcesses = MAX_PROCESSES;

    // Populate the array with processes and assign random burst times
    for (int i = 0; i < numProcesses; ++i) {
        processes[i] = {i + 1, rand() % 27 + 1, rand() % 27 + 1, 0, false};
        readyQueue.push(&processes[i]); // Add each process to the ready queue initially
    }

    pthread_t schedulerThread;

    // Create the FCFS scheduler thread
    pthread_create(&schedulerThread, nullptr, FCFS, nullptr);

    // Wait for the scheduler thread to complete
    pthread_join(schedulerThread, nullptr);

    return 0;
}
