#include <stdio.h>

void executeFCFS(int process_ids[], int arrival_times[], int burst_times[], int n) {
    int total_waiting_time = 0;  // Total waiting time
    int total_turnaround_time = 0;  // Total turnaround time

    int current_time = 0;

    printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        int waiting_time = current_time - arrival_times[i];
        if (waiting_time < 0) {
            waiting_time = 0;
        }

        int turnaround_time = waiting_time + burst_times[i];

        total_waiting_time += waiting_time;
        total_turnaround_time += turnaround_time;

        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", process_ids[i], arrival_times[i], burst_times[i], waiting_time, turnaround_time);

        current_time += burst_times[i];
    }

    float avg_waiting_time = (float)total_waiting_time / n;
    float avg_turnaround_time = (float)total_turnaround_time / n;

    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
}

int main() {
    int n;  // Number of processes

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int process_ids[n];
    int arrival_times[n];
    int burst_times[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        process_ids[i] = i + 1;
        arrival_times[i] = 0;
        printf("Enter burst time for process P%d: ", i + 1);
        scanf("%d", &burst_times[i]);
    }

    executeFCFS(process_ids, arrival_times, burst_times, n);

    return 0;
}
