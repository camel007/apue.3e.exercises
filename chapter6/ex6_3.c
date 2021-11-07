#include "apue.h"
#include <stdio.h>
#include <sys/utsname.h>

int main(void) {
    struct utsname uname_str;

    int ret = uname(&uname_str);
    if (ret != 0) {
        err_ret("get uname failed\n");
    }

    printf("uname -s: %s\n", uname_str.sysname);
    printf("uname -v: %s\n", uname_str.version);
    printf("uname -m: %s\n", uname_str.machine);
    printf("uname -n: %s\n", uname_str.nodename);
    printf("uname -r: %s\n", uname_str.release);

    char buf[1024] = {0};
    sprintf(buf, "%s %s %s %s %s\n", uname_str.sysname, uname_str.nodename, uname_str.release, uname_str.version, uname_str.machine);
    printf("uaname -a: %s", buf);

    return 0;
}
