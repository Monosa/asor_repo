#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



int main(int argc, char *argv[]){
	switch(fork()){
		case -1:
			perror("Error fork");
			return -1;
		break;
		case 0:
			setsid();
			
			int fd_out = open("/tmp/daemon.out", O_CREAT | O_RDWR | O_TRUNC, 0777);
			int fd_error = open("/tmp/daemon.err", O_CREAT | O_RDWR | O_TRUNC, 0777);
			int fd_in = open("/dev/null", O_RDWR, 0777);

			int fd2 = dup2(fd_error, 2);
			int fd1 = dup2(fd_out, 1);
			int fd0 = dup2(fd_in, 0);

			close(fd_error);
			close(fd_out);
			close(fd_in);

			int ex = execvp(argv[1], argv + 1);
			if(ex == -1){
				perror("Error execvp");
				return -1;
			}
		break;
		default:
			printf("Yo soy tu padre\n");
		break;
	}

	return 0;
}