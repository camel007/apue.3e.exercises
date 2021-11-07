#include <grp.h>
#include "apue.h"

int main(int argc, const char *argv[]) {
	struct group *grp = getgrnam("SENSETIME\\Domain");
	if(grp == NULL)
	{
		err_ret("invalid group name");
	}

	char**ptr = grp->gr_mem;
	while(*ptr != NULL) {
		printf("usr name: %s\n", *ptr);
		ptr++;
	}

	return 0;
}
