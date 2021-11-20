#include "apue.h"
#include <unistd.h>
#include <sys/resource.h>
#include <sys/syslimits.h>

int main() {
	char *usr = getlogin();
	printf("%s\n", usr);
	
	printf("nzero: %d\n", NZERO);

	printf("nice: %d\n", getpriority(PRIO_PROCESS, 0));
	int n = nice(3);
	printf("nice: %d\n", n);

	return 0;
}
