#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    printf("El PID es: %i\n", getpid());

    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    sigprocmask(SIG_BLOCK, &set, NULL);
    
    int segs = atoi(argv[1]);
    sleep(segs);

    sigset_t pendset;
    sigemptyset(&pendset);
	
    if(sigpending(&pendset) == -1){
	perror("Error sispending");
	return -1;
    }

    switch(sigismember(&pendset, SIGUSR1)){
        case -1:
            perror("Error sigismember");
            return -1;
        break;
        case 0:
            printf("Borrado");
            unlink(argv[0]);
        break;
    }

    return 0;
}