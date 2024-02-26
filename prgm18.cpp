#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_ITEMS 10

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

sem_t empty;
sem_t full;
pthread_mutex_t mutex;

// Function prototypes
void *producer(void *arg);
void *consumer(void *arg);
void insertItem(int item);
int removeItem();

int main() {
    pthread_t producerThread, consumerThread;

    // Initialize semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // Create producer and consumer threads
    pthread_create(&producerThread, NULL, producer, NULL);
    pthread_create(&consumerThread, NULL, consumer, NULL);

    // Join threads
    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);

    // Destroy semaphores and mutex
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}

// Producer function
void *producer(void *arg) {
    int item;
    for (int i = 0; i < NUM_ITEMS; i++) {
        item = rand() % 100 + 1; // Generate a random item

        sem_wait(&empty); // Wait for empty buffer slot
        pthread_mutex_lock(&mutex); // Lock mutex

        insertItem(item); // Insert item into buffer

        pthread_mutex_unlock(&mutex); // Unlock mutex
        sem_post(&full); // Signal that buffer is no longer empty

        printf("Produced item: %d\n", item);
        sleep(1); // Sleep for demonstration purposes
    }
    pthread_exit(NULL);
}

// Consumer function
void *consumer(void *arg) {
    int item;
    for (int i = 0; i < NUM_ITEMS; i++) {
        sem_wait(&full); // Wait for full buffer
        pthread_mutex_lock(&mutex); // Lock mutex

        item = removeItem(); // Remove item from buffer

        pthread_mutex_unlock(&mutex); // Unlock mutex
        sem_post(&empty); // Signal that buffer is no longer full

        printf("Consumed item: %d\n", item);
        sleep(1); // Sleep for demonstration purposes
    }
    pthread_exit(NULL);
}

// Function to insert an item into the buffer
void insertItem(int item) {
    buffer[in] = item;
    in = (in + 1) % BUFFER_SIZE;
}

// Function to remove an item from the buffer
int removeItem() {
    int item = buffer[out];
    out = (out + 1) % BUFFER_SIZE;
    return item;
}

