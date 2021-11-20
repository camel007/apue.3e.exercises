#include "apue.h" 

int main(int argc, char *argv[]) {
	pid_t pid;

	pid = fork();
	if(pid < 0) {
		err_sys("fork error");
	} else if(pid == 0) {
		sleep(10);
		printf("pid = %d, ppid = %d\n", getpid(), getppid());
	}

	exit(0);
}
