#include "apue.h"
#include <sys/wait.h>

void print_string(char *str) {
	setbuf(stdout, NULL); // no buffer
	int c;
	for(char *ptr = str; (c = *ptr) != 0; ++ptr) {
		putc(c, stdout);
	}
}

int main() {
	pid_t pid;
	TELL_WAIT();
	if((pid = fork()) < 0) {
		err_sys("fork error");
	} else if(pid == 0) {
		WAIT_PARENT();
		print_string("output from xxxxxxxxxxx child\n");
		_exit(0);
	} else {
		print_string("output from xxxxxxxxx         parent\n");
		TELL_CHILD(pid);
	}

	return 0;
}
