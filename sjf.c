#include <stdio.h>

void findSJF(int n, int at[], int bt[]) {
    int ct[n], tat[n], wt[n], completed[n], current_time = 0, min_idx;
    float total_wt = 0, total_tat = 0;

    for (int i = 0; i < n; i++) completed[i] = 0; // Mark all processes as incomplete

    for (int i = 0; i < n; i++) {
        min_idx = -1;

        // Find the process with the shortest burst time that has arrived
        for (int j = 0; j < n; j++) {
            if (!completed[j] && at[j] <= current_time) {
                if (min_idx == -1 || bt[j] < bt[min_idx]) 
                    min_idx = j;
            }
        }

        // If no process is available, advance time
        if (min_idx == -1) {
            current_time++;
            i--; // Retry finding the process
            continue;
        }

        // Calculate Completion Time (CT)
        ct[min_idx] = current_time + bt[min_idx];
        current_time = ct[min_idx];
        completed[min_idx] = 1;

        // Calculate Turnaround Time (TAT) & Waiting Time (WT)
        tat[min_idx] = ct[min_idx] - at[min_idx];
        wt[min_idx] = tat[min_idx] - bt[min_idx];

        total_wt += wt[min_idx];
        total_tat += tat[min_idx];
    }

    // Print Table
    printf("P#\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) 
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);

    printf("\nAvg WT = %.2f", total_wt / n);
    printf("\nAvg TAT = %.2f\n", total_tat / n);
}

int main() {
    int at[] = {0, 1, 2, 3, 4}; // Arrival times
    int bt[] = {8, 1, 3, 2, 6}; // Burst times
    int n = sizeof(at) / sizeof(at[0]);

    findSJF(n, at, bt);
    return 0;
}
