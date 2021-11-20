#include<fcntl.h>  /*fcntl()*/
#include <stdio.h>
/*Some necessary head files*/

int main(int argc ,char *argv[])
{
    int fd,val;

    sscanf(argv[1], "%d", &fd);
    if((val = fcntl(fd,F_GETFD,0)) < 0)
        perror("fcntl");
    printf("val: %d, FD_CLOEXEC: %d, val & FD_CLOEXEC: %d\n", val, FD_CLOEXEC, (val & FD_CLOEXEC));
    if(val & FD_CLOEXEC)
        printf("close-on-exec is on\n");
    else
        printf("clsose-on-exec is off\n");
return 0;
}
