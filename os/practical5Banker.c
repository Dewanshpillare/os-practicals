#include <stdio.h>

int main() {
    // Declare variables

/*n: Number of processes - Represents the total number of processes in the system.
m: Number of resources - Represents the total number of resources in the system.
i, j, k: Loop control variables used in for loops.
*/
    int n, m, i, j, k;

    // Prompt user for the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Prompt user for the number of resources
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    // Declare matrices for allocation, maximum, and available resources
    int allocation[n][m], max_need[n][m], available_resource[m];

    // Input allocation matrix
    printf("Enter the Allocation Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Input maximum matrix
    printf("Enter the Maximum Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &max_need[i][j]);
        }
    }

    // Input available resources
    printf("Enter the Available Resources:\n");
    for (j = 0; j < m; j++) {
        scanf("%d", &available_resource[j]);
    }

    // Declare arrays for tracking processed and safe sequences
    int processed[n], safe_sequence[n], ind = 0;

    // Initialize processed array
    for (k = 0; k < n; k++) {
        processed[k] = 0;
    }

    // Calculate the remaining need matrix
    int remaining_need[n][m];
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++)
            remaining_need[i][j] = max_need[i][j] - allocation[i][j];
    }

    // Loop for the Banker's algorithm
    
    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            if (processed[i] == 0) {

                int flag = 0;

                // Check if the process can be executed
                for (j = 0; j < m; j++) {
                    if (remaining_need[i][j] > available_resource[j]) {
                        flag = 1;
                        break;
                    }
                }

                // If the process can be executed, update resources
                if (flag == 0) {
                    safe_sequence[ind++] = i;
                    for (int y = 0; y < m; y++)
                        available_resource[y] += allocation[i][y];
                    processed[i] = 1;
                }
            }
        }
    }

    // Check if the system is safe
    int flag = 1;

    for (int i = 0; i < n; i++) {
        if (processed[i] == 0) {
            flag = 0;
            printf("The following system is not safe");
            break;
        }
    }

    // Display the safe sequence if the system is safe
    if (flag == 1) {
        printf("Following is the SAFE Sequence\n");
        for (i = 0; i < n - 1; i++)
            printf(" P%d ->", safe_sequence[i]);
        printf(" P%d", safe_sequence[n - 1]);
    }

    return 0;
}
