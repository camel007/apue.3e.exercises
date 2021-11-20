#include <stdlib.h>
#include "apue.h"

int globalvar = 6;
static char buf[] = "abc\n";

int main(int argc, const char* argv[]) {
	pid_t pid;
	int var;

	var = 88;
	printf("befor vfork\n");
	if ((pid = vfork()) < 0) {
		err_sys("fork failed");
	}else if (pid == 0) {
		globalvar += 1;
		var++;
		fclose(stdout);
		close(STDOUT_FILENO);
		_exit(0);
	}

	int ret = printf("global var: %d, var: %d\n", globalvar, var);
	printf("ret: %d\n", ret);

	//close(STDOUT_FILENO);
	write(STDOUT_FILENO, buf, sizeof(buf) -1 );

	return 0;
}
