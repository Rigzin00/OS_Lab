#include <stdio.h>
#include <stdbool.h>

#define P 5 // Number of processes
#define R 3 // Number of resources

// Function to check if the system is in a safe state
bool isSafe(int avail[], int max[][R], int allot[][R]) {
    int work[R];
    bool finish[P] = {0};
    int safeSeq[P], count = 0;
//need
    int need[P][R];
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = max[i][j] - allot[i][j];

    for (int i = 0; i < R; i++)
        work[i] = avail[i];

    printf("\nSystem State (after request if any):\n");
    printf("Process\tAlloc\tMax\tNeed\tAvailable\n");

    while (count < P) {
        bool found = false;
        for (int p = 0; p < P; p++) {
            if (!finish[p]) {
                bool canAllocate = true;
                for (int j = 0; j < R; j++) {
                    if (need[p][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate) {
                    for (int j = 0; j < R; j++)
                        work[j] += allot[p][j];

                    safeSeq[count++] = p;
                    finish[p] = true;
                    found = true;

                    printf("P%d\t", p);
                    for (int j = 0; j < R; j++) printf("%d ", allot[p][j]);
                    printf("\t");
                    for (int j = 0; j < R; j++) printf("%d ", max[p][j]);
                    printf("\t");
                    for (int j = 0; j < R; j++) printf("%d ", need[p][j]);
                    printf("\t");
                    for (int j = 0; j < R; j++) printf("%d ", work[j]);
                    printf("\n");
                }
            }
        }

        if (!found)
            return false;
    }

    printf("\nSafe Sequence: ");
    for (int i = 0; i < P; i++)
        printf("P%d ", safeSeq[i]);
    printf("\n");

    return true;
}

// Function to request resources for a process
bool requestResources(int pid, int request[], int avail[], int max[][R], int allot[][R]) {
    int need[P][R];
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = max[i][j] - allot[i][j];

    // Check if request exceeds need
    for (int i = 0; i < R; i++) {
        if (request[i] > need[pid][i]) {
            printf("Error: Process %d requested more than its need.\n", pid);
            return false;
        }
    }

    // Check if request exceeds available resources
    for (int i = 0; i < R; i++) {
        if (request[i] > avail[i]) {
            printf("Error: Not enough available resources for Process %d.\n", pid);
            return false;
        }
    }

    // Try allocating temporarily
    for (int i = 0; i < R; i++) {
        avail[i] -= request[i];
        allot[pid][i] += request[i];
    }

    // Check if safe
    if (isSafe(avail, max, allot)) {
        printf("Request can be granted safely.\n");
        return true;
    } else {
        // Rollback if not safe
        for (int i = 0; i < R; i++) {
            avail[i] += request[i];
            allot[pid][i] -= request[i];
        }
        printf("Request cannot be granted (would lead to unsafe state).\n");
        return false;
    }
}

int main() {
    int avail[R], max[P][R], allot[P][R];

    printf("Enter available resources (R0 R1 R2): ");
    for (int i = 0; i < R; i++)
        scanf("%d", &avail[i]);

    for (int i = 0; i < P; i++) {
        printf("Enter Max resources for P%d: ", i);
        for (int j = 0; j < R; j++)
            scanf("%d", &max[i][j]);
    }

    for (int i = 0; i < P; i++) {
        printf("Enter Allocated resources for P%d: ", i);
        for (int j = 0; j < R; j++)
            scanf("%d", &allot[i][j]);
    }

    if (!isSafe(avail, max, allot)) {
        printf("Initial state is not safe.\n");
        return 1;
    }

    // Handle a resource request
    char choice;
    printf("\nDo you want to simulate a resource request? (y/n): ");
    scanf(" %c", &choice);
    if (choice == 'y' || choice == 'Y') {
        int pid, req[R];
        printf("Enter Process ID (0-%d): ", P - 1);
        scanf("%d", &pid);
        printf("Enter resource request (R0 R1 R2): ");
        for (int i = 0; i < R; i++)
            scanf("%d", &req[i]);
        requestResources(pid, req, avail, max, allot);
    }

    return 0;
}
