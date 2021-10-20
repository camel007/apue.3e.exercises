#include "apue.h"
#include <fcntl.h>

#define RWRWRW (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)
#define RWXRWXRWX (S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IWOTH | S_IXOTH)

int main(int argc, const char *argv[]){
    umask(0);

    if(creat("foo", RWRWRW) < 0)
        err_sys("create error for foo");

    umask(RWXRWXRWX);
    if(creat("bar", RWRWRW)){
        err_sys("create error for bar");
    }

    exit(0);
}