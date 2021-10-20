#include "apue.h"
#include <fcntl.h>

#define RWRWRW (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)
#define WRWRW (S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)

int main(int argc, const char *argv[]){
    umask(0);
    extern int errno;

    if(open("foo", O_EXCL | O_CREAT)){
        unlink("foo");
        printf("foo exist, delete it first\n");
    }

    if(creat("foo", RWRWRW) < 0)
        err_sys("create error for foo");

    if(chmod("foo", WRWRW)){
        err_sys("chmod error for foo");
    }

    int fd = open("foo", O_RDONLY);
    if(fd == -1) {
        printf("open error for foo, errno: %s\n", strerror(errno));
    }

    exit(0);
}