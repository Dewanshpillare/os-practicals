#include <stdio.h>

int main() {
    int n, time_quantum;

    // Input: Number of processes and time quantum
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter time quantum: ");
    scanf("%d", &time_quantum);

    // Process details
    int burst_time[n], remaining_time[n], waiting_time[n], turnaround_time[n], arrival_time[n];

    // Input: Burst times and arrival times for each process
    for (int i = 0; i < n; i++) {
        printf("Enter burst time for process P%d: ", i + 1);
        scanf("%d", &burst_time[i]);

        printf("Enter arrival time for process P%d: ", i + 1);
        scanf("%d", &arrival_time[i]);

        remaining_time[i] = burst_time[i];
    }

    int current_time = 0, completed = 0;

    // Round Robin Scheduling
    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (arrival_time[i] <= current_time && remaining_time[i] > 0) {
                if (remaining_time[i] <= time_quantum) {
                    // Process completes
                    current_time += remaining_time[i];
                    turnaround_time[i] = current_time - arrival_time[i];
                    waiting_time[i] = turnaround_time[i] - burst_time[i];
                    remaining_time[i] = 0;
                    completed++;
                } else {
                    // Process continues in the next round
                    current_time += time_quantum;
                    remaining_time[i] -= time_quantum;
                }
            }
        }
    }

    // Output: Display process details and averages
    double avg_waiting_time = 0, avg_turnaround_time = 0;

    printf("\n\nProcess\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, burst_time[i], arrival_time[i], waiting_time[i], turnaround_time[i]);
        avg_waiting_time += waiting_time[i];
        avg_turnaround_time += turnaround_time[i];
    }

    avg_waiting_time /= n;
    avg_turnaround_time /= n;

    printf("\nAverage Waiting Time: %.2lf", avg_waiting_time);
    printf("\nAverage Turnaround Time: %.2lf\n", avg_turnaround_time);

    return 0;
}
