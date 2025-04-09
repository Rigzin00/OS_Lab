#include <stdio.h>

// Function to calculate waiting time
void findWaitingTime(int n, int bt[], int wt[], int at[]) {
    wt[0] = 0;
    for (int i = 1; i < n; i++) {
        int service_time = at[i - 1] + wt[i - 1] + bt[i - 1];
        wt[i] = service_time - at[i];
        if (wt[i] < 0)
            wt[i] = 0;
    }
}

// Function to calculate turnaround time
void findTurnAroundTime(int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = wt[i] + bt[i];
    }
}

// Function to calculate completion time
void findCompletionTime(int n, int at[], int tat[], int ct[]) {
    for (int i = 0; i < n; i++) {
        ct[i] = at[i] + tat[i];
    }
}

// Function to display everything
void findAvgTime(int processes[], int n, int bt[], int at[]) {
    int wt[n], tat[n], ct[n];
    float total_wt = 0, total_tat = 0;

    findWaitingTime(n, bt, wt, at);
    findTurnAroundTime(n, bt, wt, tat);
    findCompletionTime(n, at, tat, ct);

    printf("\nProcess\tAT\tBT\tCT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", processes[i], at[i], bt[i], ct[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f\n", total_wt / n);
    printf("Average Turnaround Time = %.2f\n", total_tat / n);

    // Gantt Chart
    printf("\nGantt Chart:\n|");
    int current_time = 0;
    for (int i = 0; i < n; i++) {
        if (at[i] > current_time)
            current_time = at[i]; // CPU idle time
        printf(" P%d |", processes[i]);
        current_time += bt[i];
    }

    // Time Line
    printf("\n0");
    current_time = 0;
    for (int i = 0; i < n; i++) {
        if (at[i] > current_time)
            current_time = at[i];
        current_time += bt[i];
        printf("\t%d", current_time);
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int processes[n], bt[n], at[n];
    for (int i = 0; i < n; i++) {
        processes[i] = i + 1;
        printf("Enter Arrival Time and Burst Time for Process P%d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
    }

    findAvgTime(processes, n, bt, at);

    return 0;
}
