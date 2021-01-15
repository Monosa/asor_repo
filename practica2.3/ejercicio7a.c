#include <stdlib.h>
#include <stdio.h>


int main(int argc, char *argv[]){
	int sys = system(argv[1]);

	if(sys == -1){
		perror("Error system");
		return -1;
	}

	printf("El comando termino de ejecutarse\n");

	return 0;
}
