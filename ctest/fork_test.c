#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
   pid_t pid = fork();
   int stat = 0;
   switch(pid) {
   case -1:
       perror("fork failed");
       exit(1);
       break;
   case 0:
       printf("\n");
       sleep(20);
       execlp("ps", "ps", "au", 0);
       break;
   default:
       pid = wait(&stat);
       printf("Child has finished: PID = %d\n", pid);
       if(WIFEXITED(stat)) 
           printf("Child exited with code %d\n", WEXITSTATUS(stat));
       else
           printf("Child terminated abnormally\n");

       printf("Parent, ps Done\n");
       break;
   }  

    exit(0);
}
