#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Global variables
int mutex = 1;          // Mutex to control access to critical sections
int full = 0;           // Number of full slots in the buffer
int empty = 10;         // Number of empty slots in the buffer
int x = 0;              // Counter for produced and consumed items

pthread_mutex_t lock;   // Mutex variable for synchronization

// Function to simulate item production by the producer
void producer() {
    pthread_mutex_lock(&lock);  // Acquire the lock

    // Check conditions for production
    if ((mutex == 1) && (empty != 0)) {
        --mutex;
        ++full;
        --empty;
        x++;
        printf("\nProducer produces item %d\n", x);
        ++mutex;
    } else {
        printf("Buffer is full!\n");
    }

    pthread_mutex_unlock(&lock);  // Release the lock
}

// Function to simulate item consumption by the consumer
void consumer() {
    pthread_mutex_lock(&lock);  // Acquire the lock

    // Check conditions for consumption
    if ((mutex == 1) && (full != 0)) {
        --mutex;
        --full;
        ++empty;
        printf("\nConsumer consumes item %d\n", x);
        x--;
        ++mutex;
    } else {
        printf("Buffer is empty!\n");
    }

    pthread_mutex_unlock(&lock);  // Release the lock
}

// Function to be executed by the producer thread
void* producerThread(void* arg) {
    for (int i = 0; i < 5; ++i) {
        producer();
    }
    return NULL;
}

// Function to be executed by the consumer thread
void* consumerThread(void* arg) {
    for (int i = 0; i < 5; ++i) {
        consumer();
    }
    return NULL;
}

int main() {
    pthread_t producerThreadID, consumerThreadID;

    pthread_mutex_init(&lock, NULL);  // Initialize the mutex

    // Create producer and consumer threads
    pthread_create(&producerThreadID, NULL, producerThread, NULL);
    pthread_create(&consumerThreadID, NULL, consumerThread, NULL);

    // Wait for threads to finish
    pthread_join(producerThreadID, NULL);
    pthread_join(consumerThreadID, NULL);

    pthread_mutex_destroy(&lock);  // Destroy the mutex

    return 0;
}
