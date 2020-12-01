#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <pwd.h>


int main(){
	printf("UID Real: %d\n", getuid());
	printf("UID Efectivo: %d\n", geteuid());

	uid_t uid = getuid();
	struct passwd *password;
	password = getpwuid(uid);

	char *user = password->pw_name;
	char *home = password->pw_dir;
	char *info = password->pw_gecos;
	printf("Nombre de usuario: %s\n", user);
	printf("Directorio Home: %s\n", home);
	printf("Descripcion del usuario: %s\n", info);

	return 1;
}