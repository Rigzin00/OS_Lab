#include <stdio.h>
#include <stdbool.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
};

// Function to sort processes by arrival time
void sortByArrivalTime(struct Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

// Function to find the shortest job available at a given time
int findNextProcess(struct Process processes[], bool completed[], int n, int current_time) {
    int shortest_index = -1;
    int shortest_burst = 1e9; // Large number

    for (int i = 0; i < n; i++) {
        if (!completed[i] && processes[i].arrival_time <= current_time) {
            if (processes[i].burst_time < shortest_burst) {
                shortest_burst = processes[i].burst_time;
                shortest_index = i;
            }
        }
    }
    return shortest_index;
}

// Function to calculate waiting and turnaround times
void calculateAvgTimes(struct Process processes[], int n) {
    bool completed[n];
    int wt[n], tat[n], completion_time[n];
    int current_time = 0, completed_count = 0;

    // Initialize completed array
    for (int i = 0; i < n; i++) {
        completed[i] = false;
    }

    while (completed_count < n) {
        int index = findNextProcess(processes, completed, n, current_time);

        if (index == -1) {
            // No process available, move time forward
            current_time++;
        } else {
            // Process the shortest available job
            completion_time[index] = current_time + processes[index].burst_time;
            tat[index] = completion_time[index] - processes[index].arrival_time;
            wt[index] = tat[index] - processes[index].burst_time;
            completed[index] = true;
            completed_count++;
            current_time = completion_time[index]; // Update current time
        }
    }

    // Display results
    float avg_wt = 0, avg_tat = 0;
    printf("PID\tAT\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        avg_wt += wt[i];
        avg_tat += tat[i];
        printf("%d\t%d\t%d\t%d\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time, wt[i], tat[i]);
    }

    printf("Average Waiting Time = %.2f\n", avg_wt / n);
    printf("Average Turnaround Time = %.2f\n", avg_tat / n);
}

int main() {
    int n = 5;
    struct Process processes[] = {
        {1, 0, 8},
        {2, 1, 1},
        {3, 2, 3},
        {4, 3, 2},
        {5, 4, 6}
    };

    // Step 1: Sort by arrival time
    sortByArrivalTime(processes, n);

    // Step 2: Compute and display average times
    calculateAvgTimes(processes, n);

    return 0;
}
