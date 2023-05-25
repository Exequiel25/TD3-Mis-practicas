#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdbool.h>

bool child_terminated = true;

void sigchld_handler() {
   int status, pid;
   pid = wait(&status);
   printf("Se recibió la señal SIGCHLD. El pid es %d, el exit status es %d\n", pid, status);
   child_terminated = true;
}

int main ()
{
   int pid;

   printf("Soy el padre, mi PID es %d\n", getpid());
   pid = fork();

   if (pid == 0) {
	   printf("Soy el hijo, mi pid es %d y el de mi padre es %d\n", getpid(), getppid());
	   sleep(2);
	   printf("Seré un zombie\n");
	   exit(0);
   } else {
	   sleep(10);
	   signal(SIGCHLD, sigchld_handler);
	   if (child_terminated) {
       	      printf("El hijo ha terminado, ya no está en estado zombie\n");
   	   }
   }

   exit(0);
}
