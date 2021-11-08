#include "apue.h"

#include <stdlib.h>

int process() {
	char *var = getenv("var");
	if(var == NULL) {
		err_sys("get env name %s failed\n", "var");
		return -1;
	}
	printf("%s, %d, var: %s\n", __FUNCTION__, __LINE__, var);

	return 0;
}

int main(int argc, const char *argv[]) {

	char *var = "abc";
	int ret = setenv("var", var, 1);
	if(ret != 0) {
		err_ret("put env failed\n");
	}
	process();

	return 0;
}
