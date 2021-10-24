#include "apue.h"
#include <fcntl.h>
#include <sys/time.h>
#include <sys/stat.h>

int main(int argc, const char *argv[]){

    if(argc < 2){
        printf("usage: %s <filepath>\n", argv[0]);
        return 0;
    }
    const char *filepath = argv[1];

    struct stat statbuf;
    if(stat(filepath, &statbuf) < 0){
        err_ret("stat file %s failed\n", filepath);
    }

    int fd;
    if((fd = open(filepath, O_RDWR | O_TRUNC)) < 0){
        err_ret("open failed\n");
    }

    struct timeval times[2];
    // 修改时间不改变
    times[1].tv_sec = statbuf.st_mtime;
    times[1].tv_usec = statbuf.st_mtimensec * 1000;
    // times[0].tv_sec = statbuf.st_atime;
    // times[0].tv_usec = statbuf.st_atimensec * 1000;
    // 访问时间设置为现在
    gettimeofday(&times[0], NULL);
    printf("%ld, %d\n", times[1].tv_sec, times[1].tv_usec);

    if(utimes(filepath, times) < 0) {
        err_sys("set foo utimes fail\n");
    }

    return 0;
}