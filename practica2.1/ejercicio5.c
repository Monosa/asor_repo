#include <sys/utsname.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(){
	struct utsname buf;
	int error;
	error = uname(&buf);

	if(error == -1){
		perror("uname");
		return -1;
	}

	printf("Sistema: %s\n", buf.sysname);
	printf("Nombre del host: %s\n", buf.nodename);
	printf("SO Release: %s\n", buf.release);
	printf("Version: %s\n", buf.version);
	printf("Id Maquina: %s\n", buf.machine);
	//printf("Nombre del dominio: %s\n", buf.domainname);

	return 1;
}