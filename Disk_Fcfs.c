#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

// Function to calculate total seek time using FCFS algorithm
int calculateTotalSeekTime(int *requests, int numRequests) {
    int totalSeekTime = 0;
    int currentTrack = 0; // Start at track 0

    // Iterate through each request
    for (int i = 0; i < numRequests; i++) {
        // Calculate seek time for current request
        int seekTime = abs(currentTrack - requests[i]);
        
        // Update current track to the requested track
        currentTrack = requests[i];

        // Add seek time for this request to total seek time
        totalSeekTime += seekTime;
    }

    return totalSeekTime;
}

int main() {
    int requests[MAX_REQUESTS];
    int numRequests;

    // Input number of disk requests
    printf("Enter the number of disk requests: ");
    scanf("%d", &numRequests);

    if (numRequests <= 0 || numRequests > MAX_REQUESTS) {
        printf("Invalid number of requests.\n");
        return 1;
    }

    // Input disk requests
    printf("Enter the disk requests (track numbers):\n");
    for (int i = 0; i < numRequests; i++) {
        scanf("%d", &requests[i]);
    }

    // Calculate and print total seek time
    int totalSeekTime = calculateTotalSeekTime(requests, numRequests);
    printf("Total seek time using FCFS: %d\n", totalSeekTime);

    return 0;
}