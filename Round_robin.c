#include <stdio.h>

// Structure to represent a process
struct Process {
    int id;
    int burst_time;
};

// Function to simulate Round Robin scheduling
void roundRobin(struct Process processes[], int n, int time_quantum) {
    int remaining_time[n], completion_time[n], tat[n], wt[n];
    for (int i = 0; i < n; ++i)
        remaining_time[i] = processes[i].burst_time;

    int current_time = 0;
    int completed = 0;

    while (completed < n) {
        int flag = 0;
        for (int i = 0; i < n; ++i) {
            if (remaining_time[i] > 0) {
                flag = 1; // At least one process is pending
                if (remaining_time[i] <= time_quantum) {
                    // Process completes in this cycle
                    current_time += remaining_time[i];
                    remaining_time[i] = 0;
                    completion_time[i] = current_time;
                    completed++;
                } else {
                    // Process runs for time_quantum and remains in the queue
                    current_time += time_quantum;
                    remaining_time[i] -= time_quantum;
                }
            }
        }
        if (!flag) break; // If no process is left, exit loop
    }

    // Calculate Turnaround Time (TAT) and Waiting Time (WT)
    float total_wt = 0, total_tat = 0;
    printf("\nPID\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        tat[i] = completion_time[i];  // Since arrival time is 0, TAT = CT - AT (AT=0)
        wt[i] = tat[i] - processes[i].burst_time;

        total_wt += wt[i];
        total_tat += tat[i];

        printf("%d\t%d\t%d\t%d\t%d\n", processes[i].id, processes[i].burst_time, completion_time[i], tat[i], wt[i]);
    }

    printf("\nAverage Waiting Time = %.2f\n", total_wt / n);
    printf("Average Turnaround Time = %.2f\n", total_tat / n);
}

int main() {
    int n = 3; // Number of processes
    struct Process processes[] = {{1, 4}, {2, 3}, {3, 5}};
    int time_quantum = 2;

    printf("Round Robin Scheduling:\n");
    roundRobin(processes, n, time_quantum);

    return 0;
}
