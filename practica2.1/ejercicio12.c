#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	time_t t = time(NULL);
	printf("Segundos transcurridos desde el Epoch: %li\n", t);

	return 1;
}