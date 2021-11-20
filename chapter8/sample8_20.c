#include "apue.h"
#include <sys/wait.h>

int main(void) {

	pid_t pid;

	if((pid = fork()) < 0) {
		err_sys("fork error");
	}else if(pid == 0) {
		if(execl("/Users/zhangyao/Documents/github/apue.3e.exercises/chapter8/python_interpreter", "python_interpreter", "abc", "def", (char*)0) < 0)
		{
			err_sys("execl fail");
		}
	}

	if(waitpid(pid, NULL, 0) != pid) {
		err_sys("wait error");
	}

	return 0;
}
