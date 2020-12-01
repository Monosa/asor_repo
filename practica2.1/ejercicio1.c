#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

int main(){
	char *error;
	if(setuid(0) == -1){
		perror(error);		
	}
	return 1;
}
