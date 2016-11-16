#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>

static void sighandler( int signo ){
  if (signo == SIGINT){
    int f = open("sigfile.txt", O_CREAT|O_WRONLY|O_APPEND, 0644);
    char txt[] = "exited process\n";
    write(f, txt, sizeof(txt));
    close(f);
    exit(0);
  }
  else if (signo == SIGUSR1){
    printf("parental P-I-D appears to be: %d\n", getppid());
  }
}

int main(){
  signal(SIGINT, sighandler);
  signal(SIGUSR1, sighandler);
  while(1){
    printf("the P-I-D of me appears to be: %d\n", getpid());
    sleep(1);
  }
}
