#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

int open(const char *pathname, int flags);

size_t strlen(const char *s);



ssize_t read(int fd, void *buf, size_t count);

int main(int argc, char *argv[]]{
	char buf[256];
	
	int fd = open("./nametub", O_RDONLY | O_NONBLOCK);
	int fd2 = open("./nametub2", O_RDONLY | O_NONBLOCK);
	
	if(fd == -1 || fd2 == -1){
		perror("Error open");
		close(fd);
		close(fd2);
		return -1;
	}

	int listo = 0;
	
	
	while(listo != -1){
		fd_set tubs; //Crea el set 
		FD_ZERO(&tubs); //limpia el set
		FD_SET(fd, &tubs); //Llena el set
		FD_SET(fd2, &tubs); //Llena el set
		int ntub, curtub;

		listo = select((fd < fd2) ? fd2 +1 : fd + 1, &tubs, NULL, NULL, NULL);
		/*
		int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, 				struct timeval *timeout);
		nfds  is the highest-numbered file descriptor in any of the three sets, plus 1.
		*/

		if(listo > 0){
			if(FD_ISSET(fd, &tubs)){
				ntub = 1;
				curtub = fd;
			}
			if(FD_ISSET(fd2, &tubs)){
				ntub = 2;
				curtub = fd2;
			}
			
			ssize_t rs = 255;
			while (rs == 255) {

				rs = read(curtub, buf, 255);

				if (rs == -1) {
					perror("Error read");
					close(fd);
					close(fd2);
					return -1;
				}

				buf[rs] = '\0';
				printf("Tuberia %i: %s", ntub, buf);
			}
			
			 if (rs != 255 && ntub == 1) {
        			close(fd);
        			fd = open("./nametub", O_RDONLY | O_NONBLOCK);
				if (fd == -1) {
					perror("Error open");
					close(fd);
					close(fd2);
					return -1;
				}
      			} else if(rs != 255 && ntub == 2) {
        			close(fd2);
        			fd2 = open("./nametub2", O_RDONLY | O_NONBLOCK);
				if (fd2 == -1) {
					perror("Error open");
					close(fd);
					close(fd2);
					return -1;
				}
      			}
				
		}
	}
	close(fd);
  	close(fd2);
	return 0;
}