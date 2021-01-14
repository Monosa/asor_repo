#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	pid_t pid = getpid();

	printf("Identificador de proceso: %i\n", pid);
	printf("Identificador de proceso padre: %i\n", getppid());
	printf("Identificador de grupo de procesos: %i\n", getpgid(pid));
	printf("Identificador de sesion: %i\n", getsid(pid));

	struct rlimit rl;
	
	int limit = getrlimit(RLIMIT_NOFILE, &rl);

	if(limit == -1){
		perror("Error getrlimit");
		return -1;
	}

	printf("Numero maximo de ficheros que puede abrir el proceso: %i\n", rl.rlim_max);
	
	
	
	char *p = (char *)malloc(sizeof(char)*255);

	if(getcwd(p, 255) == NULL){
		perror("Error getcwd");
		return -1;
	}
	printf("Directorio de trabajo actual: %s\n", p);	
	free(p);	

	return 0;
}