#include "apue.h"
#include <sys/wait.h>

static void test_vfork();
static void test_func();

int main(){
	printf("first main pid = %d, ppid=%d\n", getpid(), getppid());	
	printf("before fork\n");
	test_vfork();
	printf("after fork\n");

	printf("second main pid = %d, ppid=%d\n", getpid(),getppid());

	printf("before normal\n");
	test_func();
	printf("after normal\n");

	exit(0);
}

static void test_vfork() {
	printf("begin fork function pid = %d,ppid = %d\n", getpid(), getppid());
	int var = 6;

	pid_t pid;

	//pid = fork();
	pid = vfork();
	if(pid < 0) {
		err_sys("vfork error");
	} else if(pid == 0) {
		var += 1;
		printf("child process pid = %d,ppid = %d\n", getpid(), getppid());
		execl("/bin/ls", "ls", ".", (char *)0);
		//_exit(0);
	} 
#if 1
	else{
		if(waitpid(pid, NULL, 0) < 0) {
			err_sys("wait error");
		}
	}
#endif
	printf("end fork function var = %d, pid = %d,ppid = %d\n", var, getpid(), getppid());
}

static void test_func() {
	printf("normal function pid = %d,ppid = %d\n", getpid(),getppid());
}
