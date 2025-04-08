#include <stdio.h>
#include <stdbool.h>

#define P 5 // Number of processes
#define R 3 // Number of resources

// Function to check if the system is in a safe state
bool isSafe(int avail[], int max[][R], int allot[][R]) {
    bool finish[P] = {0};
    int safeSeq[P];
    int need[P][R];

    // Calculate need matrix
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = max[i][j] - allot[i][j];

    int work[R];
    for (int i = 0; i < R; i++)
        work[i] = avail[i];
    printf("Process\tAlloc\tMax\tNeed\tAvailable\n");

    int count = 0;
    while (count < P) {
        bool found = false;
        for (int i = 0; i < P; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < R; j++) {
                    if (need[i][j] > work[j])
                        break;
                }

                if (j == R) {
                    for (int k = 0; k < R; k++)
                        work[k] += allot[i][k];

                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;

                    printf("P%d\t", i);
                    for (int k = 0; k < R; k++) printf("%d ", allot[i][k]);
                    printf("\t");
                    for (int k = 0; k < R; k++) printf("%d ", max[i][k]);
                    printf("\t");
                    for (int k = 0; k < R; k++) printf("%d ", need[i][k]);
                    printf("\t");
                    for (int k = 0; k < R; k++) printf("%d ", work[k]);
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

    return 0;
}
