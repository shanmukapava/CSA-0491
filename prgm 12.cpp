#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t forks[NUM_PHILOSOPHERS];

// Function for philosopher to pick up forks
void pick_up_forks(int philosopher_number) {
    pthread_mutex_lock(&forks[philosopher_number]);
    pthread_mutex_lock(&forks[(philosopher_number + 1) % NUM_PHILOSOPHERS]);
    printf("Philosopher %d is eating\n", philosopher_number);
}

// Function for philosopher to put down forks
void put_down_forks(int philosopher_number) {
    pthread_mutex_unlock(&forks[philosopher_number]);
    pthread_mutex_unlock(&forks[(philosopher_number + 1) % NUM_PHILOSOPHERS]);
    printf("Philosopher %d finished eating and is thinking\n", philosopher_number);
}

// Function for the philosopher thread
void *philosopher(void *arg) {
    int philosopher_number = *(int *)arg;

    while (1) {
        // Thinking
        sleep(rand() % 5 + 1);

        // Hungry
        pick_up_forks(philosopher_number);

        // Eating
        sleep(rand() % 3 + 1);

        // Finished eating
        put_down_forks(philosopher_number);
    }
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_numbers[NUM_PHILOSOPHERS];

    // Initialize mutex locks for each fork
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosopher_numbers[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_numbers[i]);
    }

    // Join philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy mutex locks
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}

