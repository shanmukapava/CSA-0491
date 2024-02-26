#include <stdio.h>

#define MAX_PROCESS 10

struct Process {
    int processID;
    int arrivalTime;
    int burstTime;
    int remainingTime;
};

void roundRobin(struct Process processes[], int n, int quantum) {
    int currentTime = 0;
    int completed = 0;

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].remainingTime > 0) {
                int executeTime = (processes[i].remainingTime < quantum) ? processes[i].remainingTime : quantum;
                processes[i].remainingTime -= executeTime;
                currentTime += executeTime;

                if (processes[i].remainingTime <= 0) {
                    completed++;
                    processes[i].remainingTime = 0;
                    printf("Process %d completed at time %d\n", processes[i].processID, currentTime);
                } else {
                    printf("Process %d executed for %d units at time %d\n", processes[i].processID, executeTime, currentTime);
                }
            }
        }
    }
}

int main() {
    int n, quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[MAX_PROCESS];

    printf("Enter quantum time: ");
    scanf("%d", &quantum);

    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrivalTime, &processes[i].burstTime);
        processes[i].processID = i + 1;
        processes[i].remainingTime = processes[i].burstTime;
    }

    roundRobin(processes, n, quantum);

    return 0;
}

