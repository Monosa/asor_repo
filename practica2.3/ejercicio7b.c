#include <stdio.h>
#include <unistd.h>


int main(int argc, char *argv[]){
	int ex = execvp(argv[1], argv + 1);

	if(ex == -1){
		perror("Error execvp");
		return -1;
	}

	printf("El comando termino de ejecutarse\n");

	return 0;
}
