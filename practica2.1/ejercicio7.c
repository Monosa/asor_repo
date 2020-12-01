#include <unistd.h>
#include <stdio.h>

int main(){
	printf("Numero maximo de enlaces: %li\n", pathconf("/home/cursoredes/p21", _PC_LINK_MAX));
	printf("Tamanio maximo de ruta: %li\n", pathconf("/home/cursoredes/p21", _PC_PATH_MAX));
	printf("Tamanio maximo de nombre de fichero: %li\n", pathconf("/home/cursoredes/p21", _PC_NAME_MAX));

	return 1;
}