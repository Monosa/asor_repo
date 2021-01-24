#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
	struct addrinfo hints;
	struct addrinfo *res, *i;
	
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
        hints.ai_flags = AI_PASSIVE;

	if(getaddrinfo(argv[1], NULL, &hints, &res) != 0){
		perror("Error getaddrinfo");
		return -1;
	}

	for (i = res; i != NULL; i = i->ai_next) {
		char host[NI_MAXHOST];
	 	if(getnameinfo(i->ai_addr, i->ai_addrlen, host, NI_MAXHOST, NULL, 0, NI_NUMERICSERV) != 0){
			perror("Error getnameinfo");
			return -1;
		}
		printf("Host: %s\n", host);
      		printf("Familia: %i\n", i->ai_family);
      		printf("Tipo socket: %i\n", i->ai_socktype);
	}


	freeaddrinfo(res);	

	return 0;
}