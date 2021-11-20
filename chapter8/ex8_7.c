#include<dirent.h> /*opendir()*/
#include<unistd.h> /*execl(),fcntl()*/
#include <fcntl.h>
#include <stdio.h>
#include "apue.h"

int main(void)
{
    DIR *dir;
    int val, fd;
    char buf[10]; /*for save fd*/

    dir = opendir("/");
    fd = dirfd(dir);

    if((val = fcntl(fd,F_GETFD,0)) < 0)
        perror("fcntl");
    if(val & FD_CLOEXEC)
        printf("close-on-exec is on\n");
    else
        printf("clsose-on-exec is off\n");

#if 0
    val &= ~FD_CLOEXEC;
    fcntl(fd,F_SETFD,val);
#endif
    sprintf(buf,"%d\n",fd);

    pid_t pid;
    if((pid = fork()) < 0)
        perror("fork");
    else if(pid == 0)
    {
        execl("/Users/zhangyao/Documents/github/apue.3e.exercises/chapter8/build/ex8_7_child","ex8_7_child",buf,NULL);
        exit(0);
    }

    return 0;
}
