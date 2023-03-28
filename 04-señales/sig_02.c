#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdbool.h>

/*
void manejador_senial(int a){
   
}
*/

int main ()
{
  signal(SIGKILL, SIG_IGN);
  // Siguiente instrucción corresponde al ejercicio 3
  signal(SIGSTOP, SIG_IGN);  //Ctrl + Z
   
   printf("Proceso PID = %d\n", getpid());   
   
   while(true);
   
   exit(0);
}
