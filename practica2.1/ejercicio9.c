#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main(){
	printf("UID Real: %d\n", getuid());
	printf("UID Efectivo: %d\n", geteuid());

	return 1;
}

// Podriamos asegurar que el fichero del programa tiene activado el setuid cuando el uid y el 
// 	euid son distintos