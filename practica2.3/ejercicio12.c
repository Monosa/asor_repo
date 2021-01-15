#include <signal.h>
#include <stdio.h>


int contINT = 0;
int contTSTP = 0;

void manejador(int signal){
	if(signal == SIGINT) contINT++;
	if(signal == SIGTSTP) contTSTP++;
}

int main(int argc, char *argv[]){
	struct sigaction act1;
	struct sigaction act2;
	
	if(sigaction(SIGINT, NULL, &act1) == -1 || sigaction(SIGINT, NULL, &act2) == -1){
		perror("Error sigaction");
		return -1;
	}

	act1.sa_handler = manejador;
	act2.sa_handler = manejador;

	int sa1 = sigaction(SIGINT, &act1, NULL);
	int sa2 = sigaction(SIGTSTP, &act2, NULL);

	if(sa1 == -1 || sa2 == -1){
		perror("Error sigaction");
		return -1;
	}

	sigset_t set;
	sigemptyset(&set);
	while(contINT + contTSTP <10)
		sigsuspend(&set);

	printf("El numero de SIGINT es: %i\n", contINT);
	printf("El numero de SIGTSTP es: %i\n", contTSTP);

	return 0;
}