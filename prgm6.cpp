#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 10

// Structure to represent a process
typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int priority;
} Process;

// Function to swap two processes
void swap(Process *xp, Process *yp) {
    Process temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// Function to perform bubble sort based on priority
void sortByPriority(Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].priority > processes[j + 1].priority) {
                swap(&processes[j], &processes[j + 1]);
            }
        }
    }
}

// Function to perform pre-emptive priority scheduling
void preemptivePriorityScheduling(Process processes[], int n) {
    int currentTime = 0;
    int completed = 0;

    while (completed < n) {
        int highestPriorityIndex = -1;
        int highestPriority = INT_MAX;

        // Find the process with the highest priority that has arrived and not completed
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= currentTime && processes[i].burst_time > 0) {
                if (processes[i].priority < highestPriority) {
                    highestPriority = processes[i].priority;
                    highestPriorityIndex = i;
                }
            }
        }

        if (highestPriorityIndex != -1) {
            // Execute the process with the highest priority for 1 unit of time
            printf("Executing process %d at time %d\n", processes[highestPriorityIndex].process_id, currentTime);
            processes[highestPriorityIndex].burst_time--;
            currentTime++;

            // If the process is completed, update completion time and mark it as completed
            if (processes[highestPriorityIndex].burst_time == 0) {
                processes[highestPriorityIndex].completion_time = currentTime;
                completed++;
            }
        } else {
            // If no process is available to execute, move to the next unit of time
            currentTime++;
        }
    }
}

int main() {
    int n;
    Process processes[MAX_PROCESSES];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter arrival time, burst time, and priority for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d %d %d", &processes[i].arrival_time, &processes[i].burst_time, &processes[i].priority);
        processes[i].process_id = i + 1;
    }

    // Sort the processes by priority
    sortByPriority(processes, n);

    // Perform pre-emptive priority scheduling
    preemptivePriorityScheduling(processes, n);

    // Display completion time for each process
    printf("\nCompletion times:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: %d\n", processes[i].process_id, processes[i].completion_time);
    }

    return 0;
}

