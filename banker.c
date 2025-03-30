#include <stdio.h>
#include <stdbool.h>

#define P 5 // Number of processes
#define R 3 // Number of resources

// Function to check if system is in a safe state
bool isSafe(int processes[], int avail[], int max[][R], int alloc[][R]) {
    int need[P][R];

    // Calculate Need matrix (Need[i][j] = Max[i][j] - Allocation[i][j])
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    // Mark all processes as unfinished
    bool finished[P] = {false};
    int safeSeq[P]; // Stores the safe sequence
    int work[R]; // Work array to track available resources
    for (int i = 0; i < R; i++)
        work[i] = avail[i];

    int count = 0; // Number of processes that can execute safely

    while (count < P) {
        bool found = false;
        for (int i = 0; i < P; i++) {
            if (!finished[i]) { // If process is not finished
                bool canAllocate = true;
                for (int j = 0; j < R; j++) {
                    if (need[i][j] > work[j]) { // Check if need exceeds available
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate) { // If resources can be allocated
                    for (int j = 0; j < R; j++)
                        work[j] += alloc[i][j]; // Free allocated resources
                    
                    safeSeq[count++] = processes[i];
                    finished[i] = true;
                    found = true;
                }
            }
        }

        if (!found) { // If no process can be safely executed, deadlock occurs
            printf("System is in an UNSAFE state! Deadlock is possible.\n");
            return false;
        }
    }

    // If all processes finished, system is in a safe state
    printf("System is in a SAFE state.\nSafe sequence: ");
    for (int i = 0; i < P; i++)
        printf("%d ", safeSeq[i]);
    printf("\n");
    return true;
}

int main() {
    int processes[P] = {0, 1, 2, 3, 4}; // Process IDs
    int available[R] = {3, 3, 2}; // Available resources
    int max[P][R] = { // Maximum demand of each process
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };
    int allocation[P][R] = { // Resources currently allocated
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    isSafe(processes, available, max, allocation);
    return 0;
}
