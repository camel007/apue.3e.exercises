#include "my_system.h"

int main(void) {
	int status;
	if ((status = my_system("date")) < 0) {
		err_sys("date error");
	}

	pr_exit(status);

	if ((status = my_system("nosuchcommand")) < 0) {
		err_sys("no such command");
	}

	pr_exit(status);

	if ((status = my_system("who; exit 44")) < 0) {
		err_sys("whoe error");
	}

	pr_exit(status);

}
