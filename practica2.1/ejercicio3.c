#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

const int MAX_ERROR = 255;

int main(){
	for(int i = 0; i < MAX_ERROR; i++){
		printf("ERROR(%d): %s\n", i, strerror(i));		
	}
	return 1;
}
