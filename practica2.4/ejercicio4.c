#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[]){
	int fd = open("./nametub", O_WRONLY | O_TRUNC);
	
	if(fd == -1){
		perror("Error open");
		close(fd);
		return -1;
	}

	size_t tam = strlen(argv[1]);
	
	if(write(fd, argv[1], tam) == -1){
		perror("Error write");
		close(fd);
		return -1;
	}	
	
	close(fd);

	return 0;
}