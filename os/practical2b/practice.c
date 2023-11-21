#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main(){

   int arr[] = {10, 2, 4, 7, 5};
   int n = sizeof(arr)/ sizeof(arr[0]);

   pid_t child_pid = fork();
   if(child_pid < 0){
      perror("Fork failed");
      exit(1);
   }
   if (child_pid == 0){
    char *args[] = {"child_program", NULL};
   }

}