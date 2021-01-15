#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGTSTP);

	int spm = sigprocmask(SIG_BLOCK, &set, NULL);
	if(spm == -1){
		perror("Error sigprocmask");
		return -1;
	}
	
	char *vent = getenv("SLEEP_SECS");
	if(vent == NULL){
		perror("Error getenv");
		return -1;
	}

	int segs = atoi(vent);
	sleep(segs);
	
	sigset_t pendset;
	sigemptyset(&pendset);
	
	if(sigpending(&pendset) == -1){
		perror("Error sispending");
		return -1;
	}

	if(sigismember(&pendset, SIGINT) == -1){
		perror("Error sigismember");		
		return -1;
	}else if(sigismember(&pendset, SIGINT) == 1){
		printf("Ha recibido la senal SIGINT\n");
	}

	if(sigismember(&pendset, SIGTSTP) == -1){
		perror("Error sigismember");		
		return -1;
	}else if(sigismember(&pendset, SIGTSTP) == 1){
		printf("Ha recibido la senal SIGTSTP\n");
		sigdelset(&set, SIGINT);
		sigprocmask(SIG_UNBLOCK, &set, NULL);
	}

	printf("Yasta");
	

	return 0;
}