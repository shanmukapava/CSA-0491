#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

// Available amount of each resource
int available[MAX_RESOURCES];

// Maximum demand of each process
int maximum[MAX_PROCESSES][MAX_RESOURCES];

// Currently allocated resources to each process
int allocation[MAX_PROCESSES][MAX_RESOURCES];

// Remaining need of each process
int need[MAX_PROCESSES][MAX_RESOURCES];

// Number of processes and resources
int num_processes, num_resources;

// Function prototypes
bool isSafe(int process, int request[]);
void releaseResources(int process, int release[]);
void printState();

int main() {
    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    printf("Enter the number of resources: ");
    scanf("%d", &num_resources);

    // Initialize available resources
    printf("Enter available resources for each resource type: ");
    for (int i = 0; i < num_resources; i++) {
        scanf("%d", &available[i]);
    }

    // Initialize maximum demand of each process
    printf("Enter maximum demand of each process for each resource type:\n");
    for (int i = 0; i < num_processes; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < num_resources; j++) {
            scanf("%d", &maximum[i][j]);
        }
    }

    // Initialize allocation and need matrices
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            allocation[i][j] = 0;
            need[i][j] = maximum[i][j];
        }
    }

    // Simulation loop
    while (true) {
        // Print current state
        printState();

        // Get process ID and resource request
        int process;
        printf("Enter process ID (-1 to exit): ");
        scanf("%d", &process);
        if (process == -1)
            break;

        int request[MAX_RESOURCES];
        printf("Enter resource request for process %d: ", process);
        for (int i = 0; i < num_resources; i++) {
            scanf("%d", &request[i]);
        }

        // Check if request can be granted
        if (isSafe(process, request)) {
            printf("Request can be granted.\n");
            releaseResources(process, request);
        } else {
            printf("Request cannot be granted. Deadlock may occur.\n");
        }
    }

    return 0;
}

// Check if the system is in a safe state after granting a request
bool isSafe(int process, int request[]) {
    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES];

    // Initialize work array and finish array
    for (int i = 0; i < num_resources; i++) {
        work[i] = available[i];
    }
    for (int i = 0; i < num_processes; i++) {
        finish[i] = false;
    }

    // Pretend to allocate resources and update work and finish arrays
    for (int i = 0; i < num_resources; i++) {
        if (request[i] > need[process][i] || request[i] > work[i]) {
            return false;
        }
    }

    for (int i = 0; i < num_resources; i++) {
        work[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }
    finish[process] = true;

    // Find a safe sequence
    int count = 0;
    int safeSequence[MAX_PROCESSES];
    while (count < num_processes) {
        bool found = false;
        for (int i = 0; i < num_processes; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < num_resources; j++) {
                    if (need[i][j] > work[j])
                        break;
                }
                if (j == num_resources) {
                    // Process can finish
                    for (int k = 0; k < num_resources; k++) {
                        work[k] += allocation[i][k];
                    }
                    finish[i] = true;
                    safeSequence[count++] = i;
                    found = true;
                }
            }
        }
        if (!found)
            break; // No safe sequence found
    }

    if (count == num_processes) {
        printf("Safe sequence: ");
        for (int i = 0; i < num_processes; i++) {
            printf("%d ", safeSequence[i]);
        }
        printf("\n");
        return true;
    } else {
        // Rollback changes
        for (int i = 0; i < num_resources; i++) {
            work[i] += request[i];
            allocation[process][i] -= request[i];
            need[process][i] += request[i];
        }
        return false;
    }
}

// Release resources allocated to a process
void releaseResources(int process, int release[]) {
    for (int i = 0; i < num_resources; i++) {
        available[i] += release[i];
        allocation[process][i] -= release[i];
        need[process][i] += release[i];
    }
}

// Print the current state of the system
void printState() {
    printf("\nCurrent state:\n");

    printf("Available resources: ");
    for (int i = 0; i < num_resources; i++) {
        printf("%d ", available[i]);
    }
    printf("\n");

    printf("Maximum demand of each process:\n");
    for (int i = 0; i < num_processes; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < num_resources; j++) {
            printf("%d ", maximum[i][j]);
        }
        printf("\n");
    }

    printf("Currently allocated resources to each process:\n");
    for (int i = 0; i < num_processes; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < num_resources; j++) {
            printf("%d ", allocation[i][j]);
        }
        printf("\n");
    }

    printf("Remaining need of each process:\n");
    for (int i = 0; i < num_processes; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < num_resources; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
}

