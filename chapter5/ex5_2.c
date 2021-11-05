#include "apue.h"
#include <stdio.h>

#define ML 4

int main(void) {

	char buf[ML];

	while ((fgets(buf, ML, stdin)) != NULL) {
		printf("call once\n");
		if (fputs(buf, stdout) == EOF) {
			err_sys("output error");
		}
	}

	if(ferror(stdin)) {
		err_sys("input error");
	}

	return 0;
}
