#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdbool.h>

void manejador_senial(int a){
   write(STDOUT_FILENO, "Me rehuso a terminar\n", sizeof("Me rehuso a terminar\n"));
}

int main ()
{
   //signal(SIGKILL, manejador_senial);
   signal(SIGUSR1, manejador_senial);

   printf("Proceso PID = %d\n", getpid());   
   
   while(true);
   
   exit(0);
}
