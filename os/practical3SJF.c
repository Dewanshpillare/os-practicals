#include <stdio.h>

int main() {
    int A[100][4];
    int n, total = 0;
    float avg_wt, avg_tat;

    // Input: number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input: burst time for each process and allocate process ID
    printf("Enter burst time:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &A[i][1]);
        A[i][0] = i + 1;
    }

    // Bubble sort to sort processes based on burst time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (A[j][1] > A[j + 1][1]) {
                // Swap burst time
                int temp = A[j][1];
                A[j][1] = A[j + 1][1];
                A[j + 1][1] = temp;

                // Swap process ID
                temp = A[j][0];
                A[j][0] = A[j + 1][0];
                A[j + 1][0] = temp;
            }
        }
    }

    // Calculate waiting times
    A[0][2] = 0;
    for (int i = 1; i < n; i++) {
        A[i][2] = 0;
        for (int j = 0; j < i; j++) {
            A[i][2] += A[j][1];
        }
        total += A[i][2];
    }

    // Calculate average waiting time
    avg_wt = (float)total / n;
    total = 0;

    // Print table header
    printf("P\tBT\tWT\tTAT\n");

    // Calculate turnaround time and print process details
    for (int i = 0; i < n; i++) {
        A[i][3] = A[i][1] + A[i][2];
        total += A[i][3];

        printf("P%d\t%d\t%d\t%d\n", A[i][0], A[i][1], A[i][2], A[i][3]);
    }

    // Calculate average turnaround time
    avg_tat = (float)total / n;

    // Print average waiting time and average turnaround time
    printf("Average Waiting Time = %f\n", avg_wt);
    printf("Average Turnaround Time = %f\n", avg_tat);

    return 0;
}
