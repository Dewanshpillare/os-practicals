#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX_REQUESTS 100
void sstf(int requests[], int n, int initial_head) {
int total_seek_time = 0;
int current_head = initial_head;
// Create an array to keep track of visited requests
int visited[MAX_REQUESTS] = {0};
for (int i = 0; i < n; i++) {
int min_seek = INT_MAX;
int next_request = -1;
// Find the next request with the shortest seek time
for (int j = 0; j < n; j++) {
if (!visited[j]) {
int seek = abs(current_head - requests[j]);
if (seek < min_seek) {
min_seek = seek;
next_request = j;
}
}
}
// Mark the selected request as visited
visited[next_request] = 1;
// Update the seek time and current head position
total_seek_time += min_seek;
current_head = requests[next_request];
printf("Move from %d to %d (Seek Time: %d)\n", current_head - min_seek,
current_head, min_seek);
}
printf("Total Seek Time: %d\n", total_seek_time);
}
int main() {
int n, initial_head;
printf("Enter the number of requests: ");
scanf("%d", &n);
if (n <= 0 || n > MAX_REQUESTS) {
printf("Invalid number of requests.\n");
return 1;
}
int requests[MAX_REQUESTS];
printf("Enter the initial head position: ");
scanf("%d", &initial_head);
printf("Enter the track positions for %d requests:\n", n);
for (int i = 0; i < n; i++) {
scanf("%d", &requests[i]);
}
sstf(requests, n, initial_head);
return 0;}
