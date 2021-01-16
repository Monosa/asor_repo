#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

volatile int borra = 1;
volatile int alarma = 0;

void manejador(int signal){
	if(signal == SIGALRM) alarma = 1;
	if(signal == SIGUSR1) borra = 0;
}

int main(int argc, char *argv[]){
	printf("Mi PID es: %i\n", getpid());

	struct sigaction act1;
	struct sigaction act2;
	
	if(sigaction(SIGALRM, NULL, &act1) == -1 || sigaction(SIGUSR1, NULL, &act2) == -1){
		perror("Error sigaction");
		return -1;
	}

	act1.sa_handler = manejador;
	act2.sa_handler = manejador;

	int sa1 = sigaction(SIGALRM, &act1, NULL);
	int sa2 = sigaction(SIGUSR1, &act2, NULL);

	if(sa1 == -1 || sa2 == -1){
		perror("Error sigaction");
		return -1;
	}

	sigset_t set;
	sigfillset(&set);
	sigdelset(&set, SIGALRM);
	sigdelset(&set, SIGUSR1);

	alarm(atoi(argv[1]));

	sigsuspend(&set);

	if(borra == 1 && alarma == 1){
		printf("Borrado");
		unlink(argv[0]);
	}

	return 0;
}
