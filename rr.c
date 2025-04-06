#include <stdio.h>
#include <stdbool.h>

// Structure to represent a process
struct Process {
    int pid;          // Process ID
    int arrival_time; // Arrival time
    int burst_time;   // Burst time
    int remaining_time; // Remaining burst time
    int completion_time; // Completion time
    int waiting_time;    // Waiting time
    int turnaround_time; // Turnaround time
    bool completed;      // Flag to check if process is completed
};

// Function to check if all processes are completed
bool allProcessesCompleted(struct Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        if (!processes[i].completed) {
            return false;
        }
    }
    return true;
}

// Function to find the next process to execute in Round Robin
int getNextProcess(struct Process processes[], int n, int current_time, int current_index) {
    int count = 0;
    int i = (current_index + 1) % n; // Start from the next process

    // Find the next process that has arrived and is not completed
    while (count < n) {
        if (processes[i].arrival_time <= current_time && !processes[i].completed && processes[i].remaining_time > 0) {
            return i;
        }
        i = (i + 1) % n;
        count++;
    }

    return -1; // No process available
}

// Function to simulate Round Robin scheduling
void roundRobin(struct Process processes[], int n, int time_quantum) {
    // Initialize remaining time for all processes
    for (int i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].completed = false;
    }

    int current_time = 0;
    int completed = 0;
    int current_process = -1;

    // Arrays for Gantt chart
    int gantt_chart[1000];
    int gantt_time[1000];
    int chart_index = 0;

    // Sort processes by arrival time (bubble sort)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    // Find the first process to execute
    for (int i = 0; i < n; i++) {
        if (processes[i].arrival_time <= current_time) {
            current_process = i;
            break;
        }
    }

    // If no process has arrived yet, advance time to the first arrival
    if (current_process == -1) {
        current_time = processes[0].arrival_time;
        current_process = 0;
    }

    // Simulate Round Robin scheduling
    while (completed < n) {
        // If current process is valid
        if (current_process != -1) {
            // Record for Gantt chart
            gantt_chart[chart_index] = processes[current_process].pid;
            gantt_time[chart_index] = current_time;
            chart_index++;

            // Calculate execution time in this time slice
            int execution_time = (processes[current_process].remaining_time < time_quantum) ?
                                 processes[current_process].remaining_time : time_quantum;

            // Update current time and remaining time
            current_time += execution_time;
            processes[current_process].remaining_time -= execution_time;

            // Check if process is completed
            if (processes[current_process].remaining_time == 0) {
                processes[current_process].completed = true;
                processes[current_process].completion_time = current_time;
                processes[current_process].turnaround_time = processes[current_process].completion_time - processes[current_process].arrival_time;
                processes[current_process].waiting_time = processes[current_process].turnaround_time - processes[current_process].burst_time;
                completed++;
            }
        } else {
            // No process available, advance time
            current_time++;
        }

        // Find the next process to execute
        current_process = getNextProcess(processes, n, current_time, current_process);

        // If no process is available, find the next arriving process
        if (current_process == -1) {
            int next_arrival_time = 999999;
            int next_process = -1;

            for (int i = 0; i < n; i++) {
                if (!processes[i].completed && processes[i].arrival_time > current_time && processes[i].arrival_time < next_arrival_time) {
                    next_arrival_time = processes[i].arrival_time;
                    next_process = i;
                }
            }

            if (next_process != -1) {
                current_time = next_arrival_time;
                current_process = next_process;
            } else {
                // All processes are completed or no more processes will arrive
                break;
            }
        }
    }

    // Add final time point for Gantt chart
    gantt_time[chart_index] = current_time;

    // Calculate average times
    float total_waiting_time = 0, total_turnaround_time = 0;

    printf("\n+----------+-------------+-----------+-------------+----------------+\n");
    printf("| Process  | Arrival Time| Burst Time| Waiting Time| Turnaround Time|\n");
    printf("+----------+-------------+-----------+-------------+----------------+\n");

    for (int i = 0; i < n; i++) {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
        printf("| P%-7d | %-11d | %-9d | %-11d | %-14d |\n",
               processes[i].pid, processes[i].arrival_time, processes[i].burst_time,
               processes[i].waiting_time, processes[i].turnaround_time);
    }

    printf("+----------+-------------+-----------+-------------+----------------+\n");
    printf("Average waiting time = %.2f\n", total_waiting_time / n);
    printf("Average turnaround time = %.2f\n", total_turnaround_time / n);

    // Print Gantt chart
    printf("\nGantt Chart:\n");
    printf("+");
    for (int i = 0; i < chart_index; i++) {
        for (int j = 0; j < 7; j++) printf("-");
        printf("+");
    }
    printf("\n|");

    for (int i = 0; i < chart_index; i++) {
        printf("  P%-3d |", gantt_chart[i]);
    }
    printf("\n+");

    for (int i = 0; i < chart_index; i++) {
        for (int j = 0; j < 7; j++) printf("-");
        printf("+");
    }
    printf("\n");

    // Print timeline
    for (int i = 0; i <= chart_index; i++) {
        printf("%-7d", gantt_time[i]);
    }
    printf("\n");
}

int main() {
    int n, time_quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    printf("\nEnter process details:\n");
    for (int i = 0; i < n; i++) {
        printf("\nProcess %d:\n", i + 1);

        processes[i].pid = i + 1;  // Process ID

        printf("Enter arrival time: ");
        scanf("%d", &processes[i].arrival_time);

        printf("Enter burst time: ");
        scanf("%d", &processes[i].burst_time);
    }

    printf("\nEnter time quantum: ");
    scanf("%d", &time_quantum);

    printf("\nRound Robin Scheduling Algorithm (Time Quantum = %d)\n", time_quantum);
    printf("=================================================\n");
    roundRobin(processes, n, time_quantum);

    return 0;
}