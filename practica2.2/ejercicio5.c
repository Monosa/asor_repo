#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int main(){


int fd = open("/home/cursoredes/p22/ejercicio5.txt", O_CREAT, 0645);


return 1;
}