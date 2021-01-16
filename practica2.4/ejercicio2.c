#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]){
	int fd0[2];
	int fd1[2];
	int p_h = pipe(fd0);
	int h_p = pipe(fd1);

	if(p_h == -1 || h_p == -1){
		perror("Error pipe");
		return -1;
	}
	
	switch(fork()){
		case -1:
			perror("Error fork");
			return -1;
		break;
		case 0: //Hijo
			close(fd0[1]);
			close(fd1[0]);
			
			int cont = 0;
			char bufS[255];
			char bufM[1] = {'l'};
			
			while(cont < 10){
				ssize_t carac = read(fd0[0], &bufS, 255);
				if(carac == -1){
					perror("[Hijo]Error read p_h");
					return -1;
				}
				
				if(write(1, &bufS, carac) == -1){
					perror("[Hijo]Error write salida");
					return -1;
				}

				cont++;

				sleep(1);

				if(cont == 10) bufM[0] = 'q';

				if(write(fd1[1], &bufM, 1) == -1){
					perror("[Hijo]Error write h_p");
					return -1;
				}
			}
			
			close(fd0[0]);
			close(fd1[1]);

			_exit(0);
		break;
		default: //Padre
			close(fd0[0]);
			close(fd1[1]);
			char bufE[255];
			char bufR[1] = {'l'}; 
			
			while(bufR[0] != 'q'){				
				ssize_t tam = read(0, &bufE, 255);
				if(tam == -1){
					perror("[Padre]Error read entrada");
					return -1;
				}
				
				if(write(fd0[1], &bufE, tam) == -1){
					perror("[Padre]Error write p_h");
					return -1;
				}
				
				while(bufR[0] != 'l' && bufR[0] != 'q'){
					if(read(fd1[0], &bufR, 1) == -1){
						perror("[Padre]Error read h_p");
						return -1;
					}
				}		
				
			}
			close(fd0[1]);
			close(fd1[0]);
		break;
	}

	return 0;
}