//C-LOOK CODE
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX_REQUESTS 100
// Function to sort an array in ascending order
void sort(int arr[], int n) {
int temp;
for (int i = 0; i < n; i++) {
for (int j = i + 1; j < n; j++) {
if (arr[i] > arr[j]) {
temp = arr[i];
arr[i] = arr[j];
arr[j] = temp;
}
}
}
}
// Function to simulate C-Look algorithm
void clook(int requests[], int n, int initial_head, int max_track) {
int total_seek_time = 0;
int current_head = initial_head;
// Sort the requests in ascending order
sort(requests, n);
// Find the index of the initial head position
int initial_index = 0;
while (initial_index < n && requests[initial_index] <= initial_head) {
initial_index++;
}
// Move the head to the right end first
total_seek_time += abs(current_head - max_track);
current_head = max_track;
printf("Move from %d to %d (Seek Time: %d)\n", initial_head, max_track,
abs(initial_head - max_track));
// Traverse the requests to the right
for (int i = initial_index; i < n; i++) {
int seek = abs(current_head - requests[i]);
total_seek_time += seek;
current_head = requests[i];
printf("Move from %d to %d (Seek Time: %d)\n", current_head - seek,
current_head, seek);
}
// Move the head to the left end
total_seek_time += abs(current_head - requests[0]);
current_head = requests[0];
printf("Move from %d to %d (Seek Time: %d)\n", max_track, requests[0],
abs(max_track - requests[0]));
// Traverse the requests to the left
for (int i = 1; i < initial_index; i++) {
int seek = abs(current_head - requests[i]);
total_seek_time += seek;
current_head = requests[i];
printf("Move from %d to %d (Seek Time: %d)\n", current_head - seek,
current_head, seek);
}
printf("Total Seek Time: %d\n", total_seek_time);
}
int main() {
int n, initial_head, max_track;
printf("Enter the number of requests: ");
scanf("%d", &n);
if (n <= 0 || n > MAX_REQUESTS) {
printf("Invalid number of requests.\n");
return 1;
}
int requests[MAX_REQUESTS];
printf("Enter the initial head position: ");
scanf("%d", &initial_head);
printf("Enter the maximum track position: ");
scanf("%d", &max_track);
printf("Enter the track positions for %d requests:\n", n);
for (int i = 0; i < n; i++) {
scanf("%d", &requests[i]);
if (requests[i] < 0 || requests[i] > max_track) {
printf("Invalid request position.\n");
return 1;
}
}
clook(requests, n, initial_head, max_track);
return 0;
}
