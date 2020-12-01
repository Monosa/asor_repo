#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>


int main(){
	time_t t = time(NULL);
	struct tm *datos = localtime(&t);

	int anio = datos->tm_year;
	
	printf("Anio: %i\n", 1900 + anio);

	return 1;
}