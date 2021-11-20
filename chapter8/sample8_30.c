#include "apue.h"
#include <errno.h>
#include <sys/time.h>
#include <sys/syslimits.h>

unsigned long long count;
struct timeval end;

void checktime(char *str) {
	struct timeval tv;

	gettimeofday(&tv, NULL);
	if(tv.tv_sec >= end.tv_sec  && tv.tv_usec >= end.tv_usec) {
		printf("%s count = %lld\n", str, count);
		exit(0);
	}
}

int main(int argc, char *argv[]) {
	pid_t pid;
	char *s;
	int nzero, ret;
	int adj = 0;

	nzero = NZERO;

	printf("NZERO %d\n", nzero);

	if(argc == 2) {
		adj = strtol(argv[1], NULL, 10);
	}
	gettimeofday(&end, NULL);
	end.tv_sec += 10;

	pid = fork();
	if(pid < 0){
		err_sys("for error");
	} else if(pid == 0) {
		s = "child";
		printf("current nice of child is %d, adjusting by %d\n", nice(0) + nzero, adj);

		errno = 0;
		if(( ret = nice(adj)) == -1) {
			err_sys("child set sechduling priority");
		}
		printf("now child nice value is %d\n", ret + nzero);
	} else {
		s = "parrent";
		printf("current nice value of parrent is %d\n", nice(0));
	}

	for(;;) {
		if(++count == 0){
			err_quit("%s counter wrap", s);
		}
		checktime(s);
	}

	exit(0);
}
