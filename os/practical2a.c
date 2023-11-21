#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Function declarations
void quickSort(int low, int high, int arr[]);
void mergeSort(int low, int high, int arr[]);
void display(int a[], int size);

int main() {
    // Variables
    int size, i;

    // Input: Number of elements to sort
    printf("Enter the number of elements you want to sort: ");
    scanf("%d", &size);

    // Arrays to store original, quick-sorted, and merge-sorted data
    int a[size], Parr[size], Carr[size];

    // Input: Elements of the array
    for (int i = 0; i < size; i++) {
        printf("Enter integer %d: \n", i + 1);
        scanf("%d", &a[i]);
        Parr[i] = Carr[i] = a[i];  // Initialize both arrays with the same values
    }

    // Create a child process
    pid_t child_pid = fork();

    if (child_pid < 0) {
        printf("Child Process Creation Failed \n");
    } else if (child_pid == 0) {
        // Child process
        printf("The child process (PID: %d) sorting using quick sort:\n", getpid());

        // Call quickSort function to sort the array in the child process
        quickSort(0, size - 1, Carr);

        printf("Sorted list by child is:\n");
        display(Carr, size);  // Display the sorted array
    } else {
        // Parent process
        printf("This is the parent process.\n");
        printf("The parent process (PID: %d) is sorting using merge sort:\n", getpid());

        // Call mergeSort function to sort the array in the parent process
        mergeSort(0, size - 1, Parr);

        printf("The merge sorted list is:");
        display(Parr, size);  // Display the sorted array

        // Wait for the child process to finish
        wait(NULL);
	// parent process sleeps for a while demonstrating zombie process
	sleep(10);
    }
}

// QuickSort implementation
void quickSort(int low, int high, int a[]) {
    int i;
    if (high > low) {
        i = low; // pivot
        for (int j = low + 1; j <= high; j++) {// iterate in array from low + 1 to highest index
            if (a[j] < a[low]) { // compares element with pivot. if it is smaller then swap it and increment i 
                i++;
                int temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
        int temp = a[low];//swap pivot to correct position
        a[low] = a[i];
        a[i] = temp;
        quickSort(low, i - 1, a);
        quickSort(i + 1, high, a);
    }
}

// MergeSort implementation
void mergeSort(int low, int high, int arr[]) {
    if (low < high) {
        int mid = (low + high) / 2;
        mergeSort(low, mid, arr);
        mergeSort(mid + 1, high, arr);

        int b[20], i = low, j = mid + 1, k = low;
        while (i <= mid && j <= high) {
            b[k++] = (arr[i] <= arr[j]) ? arr[i++] : arr[j++];
        }
        while (i <= mid) {
            b[k++] = arr[i++];
        }
        while (j <= high) {
            b[k++] = arr[j++];
        }
        for (k = low; k <= high; k++) {
            arr[k] = b[k];
        }
    }
}

// Display array elements
void display(int a[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d\t", a[i]);
    }
    printf("\n");
}
