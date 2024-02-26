#include <stdio.h>

#define MAX_PROCESSES 10

struct Process {
    int id;
    int priority;
    int burst_time;
    int completion_time;
};

void calculateCompletionTimes(struct Process processes[], int n) {
    int current_time = 0;
    for (int i = 0; i < n; i++) {
        processes[i].completion_time = current_time + processes[i].burst_time;
        current_time = processes[i].completion_time;
    }
}

void printCompletionTimes(struct Process processes[], int n) {
    printf("Process ID\tPriority\tBurst Time\tCompletion Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].priority,
               processes[i].burst_time, processes[i].completion_time);
    }
}

int main() {
    struct Process processes[MAX_PROCESSES];
    int n;

    // Input the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input details of each process
    printf("Enter priority and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Process %d: ", processes[i].id);
        scanf("%d %d", &processes[i].priority, &processes[i].burst_time);
    }

    // Calculate completion times for each process
    calculateCompletionTimes(processes, n);

    // Print completion times
    printf("\nPriority-based Scheduling:\n");
    printCompletionTimes(processes, n);

    return 0;
}
