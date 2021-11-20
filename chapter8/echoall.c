#include "apue.h"

int main(int argc, const char *argv[]) {
	int i;
	char **ptr;
	extern char **environ;

	for(i = 0; i < argc; ++i) {
		printf("[%d] argv[%d]: %s\n", getpid(), i, argv[i]);
	}
#if 0
	for(ptr = environ; *ptr != 0; ptr++) {
		printf("[%d] %s\n", getpid(), *ptr);
	}
#endif

	exit(0);
}
