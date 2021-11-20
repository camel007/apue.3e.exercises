#include "apue.h"
#include <sys/wait.h>

char *env_init[] = {"USER=unknown", "PATH=/tmp", NULL};

int main(void) {
	pid_t pid;

	printf("main process = %d\n", getpid());
	if ((pid = fork()) < 0) {
		err_sys("fork error");
	}else if(pid == 0) {
		printf("child 1 process = %d\n", getpid());
		if(execle("/Users/zhangyao/Documents/github/apue.3e.exercises/chapter8/build/echoall", "echoall", "abc", "edf", (char*)0, env_init) < 0) {
			err_sys("execle fail");
		}
	}

	if(waitpid(pid, NULL, 0) < 0) {
		err_sys("wait error");
	}

	pid_t pid1;
	if((pid1 = fork()) < 0) {
		err_sys("fork error");
	} else if (pid1 == 0) {
		printf("child 2 process = %d\n", getpid());
		if(execlp("echoall", "echoall", "ABC", "EDF", (char *)0) < 0) {
			err_sys("execlp efail\n");
		}
	}

	return 0;
}
