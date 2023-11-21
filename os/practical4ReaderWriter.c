#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t w, r; // Semaphores for writer and reader synchronization
int rc = 0; // Reader count

void* reader(void* arg) {
    sem_wait(&r); // Enter critical section for readers
    rc++;         // Increment the reader count

    if (rc == 1) {
        sem_wait(&w); // If first reader, block writers
    }

    sem_post(&r); // Exit critical section for readers

    printf("\nReader is Reading");

    sem_wait(&r); // Re-enter the critical section for readers (optimized)
    rc--;         // Decrement the reader count

    if (rc == 0) {
        sem_post(&w); // If no readers left, allow a writer to write
    }

    sem_post(&r); // Exit the critical section for readers
}

void* writer(void* arg) {
    sem_wait(&w); // Enter critical section for writers

    printf("\nWriter is Writing");

    sem_post(&w); // Exit critical section for writers
}

int main() {
    sem_init(&r, 0, 1); // Initialize reader semaphore with initial value 1
    sem_init(&w, 0, 1); // Initialize writer semaphore with initial value 1

    pthread_t write[3], read[3]; // Thread identifiers for writers and readers

    for (int i = 0; i < 3; i++) {
        pthread_create(&write[i], NULL, writer, NULL); // Create writer threads
        pthread_create(&read[i], NULL, reader, NULL);  // Create reader threads
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(write[i], NULL); // Wait for writer threads to finish
        pthread_join(read[i], NULL);  // Wait for reader threads to finish
    }

    return 0;
}
