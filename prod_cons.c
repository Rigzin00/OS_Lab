#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5  // Buffer size
#define NUM_ITEMS 10   // Number of items to produce/consume

sem_t empty, full;  // Semaphores for empty and full slots
pthread_mutex_t mutex; // Mutex for critical section

int buffer[BUFFER_SIZE]; // Shared buffer
int in = 0, out = 0;  // Buffer index pointers

void *producer(void *arg) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        int item = i + 1; // Produce an item

        sem_wait(&empty);  // Wait for an empty slot
        pthread_mutex_lock(&mutex);  // Lock the buffer

        // Critical Section: Add item to the buffer
        buffer[in] = item;
        printf("Producer produced: %d\n", item);
        in = (in + 1) % BUFFER_SIZE;  // Circular buffer

        pthread_mutex_unlock(&mutex);  // Unlock the buffer
        sem_post(&full);  // Signal that a new item is available

        sleep(1); // Simulate production time
    }
    return NULL;
}

void *consumer(void *arg) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        sem_wait(&full);  // Wait for an available item
        pthread_mutex_lock(&mutex);  // Lock the buffer

        // Critical Section: Remove item from the buffer
        int item = buffer[out];
        printf("Consumer consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;  // Circular buffer

        pthread_mutex_unlock(&mutex);  // Unlock the buffer
        sem_post(&empty);  // Signal that a slot is free

        sleep(2); // Simulate consumption time
    }
    return NULL;
}

int main() {
    pthread_t prodThread, consThread;

    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // Create producer and consumer threads
    pthread_create(&prodThread, NULL, producer, NULL);
    pthread_create(&consThread, NULL, consumer, NULL);

    // Wait for both threads to finish
    pthread_join(prodThread, NULL);
    pthread_join(consThread, NULL);

    // Destroy semaphores and mutex
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
