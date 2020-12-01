#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>


int main(){
	struct timeval tv;
	int t1 = gettimeofday(&tv, NULL);
	int start = tv.tv_usec;

	int i = 0;
	for(i; i < 1000000; i++);

	int t2 = gettimeofday(&tv, NULL);
	int stop = tv.tv_usec;
	
	printf("Tiempo transcurrido en microsegundos: %li\n", stop - start);

	return 1;
}