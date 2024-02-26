#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 5
#define NUM_WRITERS 2

sem_t mutex;        // Semaphore for mutual exclusion
sem_t wrt;          // Semaphore for controlling write access
int readers_count = 0;  // Count of active readers

void *reader(void *arg) {
    int id = *(int *)arg;
    while (1) {
        usleep(1000000);  // Sleep for a while to simulate reading time

        sem_wait(&mutex);  // Acquire mutex for updating readers_count
        readers_count++;
        if (readers_count == 1) {
            sem_wait(&wrt);  // First reader waits for writer
        }
        sem_post(&mutex);  // Release mutex

        // Reading section
        printf("Reader %d is reading\n", id);

        sem_wait(&mutex);  // Acquire mutex for updating readers_count
        readers_count--;
        if (readers_count == 0) {
            sem_post(&wrt);  // Last reader signals writer
        }
        sem_post(&mutex);  // Release mutex
    }
    return NULL;
}

void *writer(void *arg) {
    int id = *(int *)arg;
    while (1) {
        usleep(2000000);  // Sleep for a while to simulate writing time

        sem_wait(&wrt);  // Acquire wrt semaphore for writing
        // Writing section
        printf("Writer %d is writing\n", id);
        sem_post(&wrt);  // Release wrt semaphore
    }
    return NULL;
}

int main() {
    pthread_t reader_threads[NUM_READERS], writer_threads[NUM_WRITERS];
    int i, reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];

    sem_init(&mutex, 0, 1);  // Initialize mutex semaphore
    sem_init(&wrt, 0, 1);    // Initialize wrt semaphore

    // Create reader threads
    for (i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i + 1;
        if (pthread_create(&reader_threads[i], NULL, reader, &reader_ids[i]) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    // Create writer threads
    for (i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i + 1;
        if (pthread_create(&writer_threads[i], NULL, writer, &writer_ids[i]) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    // Wait for reader threads to finish
    for (i = 0; i < NUM_READERS; i++) {
        pthread_join(reader_threads[i], NULL);
    }

    // Wait for writer threads to finish
    for (i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writer_threads[i], NULL);
    }

    sem_destroy(&mutex);  // Destroy mutex semaphore
    sem_destroy(&wrt);    // Destroy wrt semaphore

    return 0;
}

