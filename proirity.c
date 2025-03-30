#include <stdio.h>

struct Process {
    int processNo;
    int arrivalTime;
    int burstTime;
    int priority;
};

// Function to sort processes based on arrival time and priority
void sortProcesses(struct Process proc[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[j].arrivalTime < proc[i].arrivalTime ||
                (proc[j].arrivalTime == proc[i].arrivalTime && proc[j].priority < proc[i].priority)) {
                struct Process temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
}

// Function to calculate waiting time (WT)
void calculateWaitingTime(struct Process proc[], int wt[], int n) {
    int completionTime = 0;
    
    wt[0] = 0; // First process starts execution immediately
    completionTime = proc[0].arrivalTime + proc[0].burstTime;

    for (int i = 1; i < n; i++) {
        // Ensure CPU waits if no process is available
        if (completionTime < proc[i].arrivalTime) {
            completionTime = proc[i].arrivalTime;
        }

        wt[i] = completionTime - proc[i].arrivalTime;
        completionTime += proc[i].burstTime; // Update completion time
    }
}

// Function to calculate turnaround time (TAT)
void calculateTurnaroundTime(struct Process proc[], int wt[], int tat[], int n) {
    for (int i = 0; i < n; i++) {
        tat[i] = proc[i].burstTime + wt[i];
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];
    int wt[n], tat[n];

    printf("Enter process details (arrival time, burst time, priority):\n");
    for (int i = 0; i < n; i++) {
        proc[i].processNo = i + 1;
        printf("P%d: ", i + 1);
        scanf("%d %d %d", &proc[i].arrivalTime, &proc[i].burstTime, &proc[i].priority);
    }

    // Sort processes based on arrival time and priority
    sortProcesses(proc, n);

    // Calculate waiting time and turnaround time
    calculateWaitingTime(proc, wt, n);
    calculateTurnaroundTime(proc, wt, tat, n);

    // Display results
    float total_wt = 0, total_tat = 0;
    printf("\nProcess\tAT\tBT\tPriority\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\n", proc[i].processNo, proc[i].arrivalTime,
               proc[i].burstTime, proc[i].priority, wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f\n", total_wt / n);
    printf("Average Turnaround Time = %.2f\n", total_tat / n);

    return 0;
}
