#include <stdio.h>

// Function to calculate Completion Time, Turnaround Time & Waiting Time
void findTimes(int processes[], int n, int at[], int bt[], int ct[], int tat[], int wt[]) {
    // First process CT
    ct[0] = at[0] + bt[0]; 

    // Calculate Completion Time (CT) for all processes
    for (int i = 1; i < n; i++)
        ct[i] = (ct[i - 1] > at[i] ? ct[i - 1] : at[i]) + bt[i];

    // Calculate Turnaround Time (TAT) = Completion Time - Arrival Time
    for (int i = 0; i < n; i++)
        tat[i] = ct[i] - at[i];

    // Calculate Waiting Time (WT) = Turnaround Time - Burst Time
    for (int i = 0; i < n; i++)
        wt[i] = tat[i] - bt[i];
}

// Function to calculate Average Waiting & Turnaround Time
void findAvgTime(int processes[], int n, int at[], int bt[]) {
    int ct[n], tat[n], wt[n];
    float total_wt = 0, total_tat = 0;

    findTimes(processes, n, at, bt, ct, tat, wt);

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf(" %d\t%d\t%d\t%d\t%d\t%d\n", processes[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);
}

int main() {
    int processes[] = {1, 2, 3, 4, 5};
    int arrival_time[] = {0, 1, 2, 3, 4}; // Processes arrive at different times
    int burst_time[] = {8, 1, 3, 2, 6};  // Burst time for each process
    int n = sizeof(processes) / sizeof(processes[0]);

    findAvgTime(processes, n, arrival_time, burst_time);
    return 0;
}
