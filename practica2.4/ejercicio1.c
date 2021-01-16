#include <unistd.h>
#include <stdio.h>

int pipe(int pipefd[2]);

int main(int argc, char *argv[]){
	int fd[2];
	int tub = pipe(fd);

	if(tub == -1){
		perror("Error pipe");
		return -1;
	}
	
	switch(fork()){
		case -1:
			perror("Error fork");
			return -1;
		break;
		case 0: //Hijo
			dup2(fd[0], 0);
			close(fd[0]);
			close(fd[1]);
			if(execlp(argv[3], argv[3], argv[4], NULL) == -1){
				perror("Error execlp en el hijo");
				return -1;
			}
		break;
		default: //Padre
			dup2(fd[1], 1);
			close(fd[0]);
			close(fd[1]);
			if(execlp(argv[1], argv[1], argv[2], NULL) == -1){
				perror("Error execlp en el padre");
				return -1;
			}

		break;
	}

	return 0;
}