#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>

int parametros(char *quien){
	pid_t pid = getpid();

	printf("[%s]: Identificador de proceso: %i\n", quien, pid);
	printf("[%s]: Identificador de proceso padre: %i\n", quien, getppid());
	printf("[%s]: Identificador de grupo de procesos: %i\n", quien, getpgid(pid));
	printf("[%s]: Identificador de sesion: %i\n", quien, getsid(pid));

	struct rlimit rl;
	int limit = getrlimit(RLIMIT_NOFILE, &rl);

	if(limit == -1){
		perror("Error getrlimit");
		return -1;
	}

	printf("[%s]: Numero maximo de ficheros que puede abrir el proceso: %i\n", quien, rl.rlim_max);
	
	
	char *p = (char *)malloc(sizeof(char)*255);

	if(getcwd(p, 255) == NULL){
		perror("Error getcwd");
		return -1;
	}

	printf("[%s]: Directorio de trabajo actual: %s\n", quien, p);	
	free(p);
}

int main(int argc, char *argv[]){
	switch(fork()){
		case -1:
			perror("Error fork");
			return -1;
		break;
		case 0:
			setsid();
			int dir = chdir("./tmp");
			if(dir == -1){
                		perror("Error chdir ");
                		return -1;
			}
			if(parametros("Hijo") == -1){
				perror("Error hijo");
				return -1;
			}
		break;
		default:
			if(parametros("Padre") == -1){
				perror("Error padre");
				return -1;
			}
		break;
	}
	return 0;
}