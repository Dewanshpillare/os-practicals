#include <stdio.h>
int main() {
    printf("Child process displaying the sorted array in reverse order:\n");
    int arr[] = {10, 5, 8, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    for (int i =0; i < n - 1; i++) {
        for (int j = 0; j < n-i-1 ; j++){
            if(arr[j] < arr[j + 1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
        
    }
    printf("The sorted array is :\n");
    for(int i=0; i<n; i++){
    printf("%d", arr[i] );
    printf("\t");
    }
    return 0;
}
