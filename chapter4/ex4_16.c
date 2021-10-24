#include "apue.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/syslimits.h>
#include <dirent.h>
#include <ftw.h>
#include <limits.h>

#define NTIMES (1024 * 1024)

#define RWX (S_IRUSR | S_IWUSR | S_IXUSR)

long total = 0;

int recursive_delete_dir(const char *dirname){
    while(chdir(dirname) != -1){
        total += 1;
        if(total == 10000){
            system("rm -rf test");
        }
    }

    printf("total: %ld\n", total);
    return 0;
}

int main(int argc, const char *argv[]){

    extern int errno;
    // recursive_dir_num("test");

    long i = 0;
    umask(0);
    printf("path max: %d\n", PATH_MAX);
    char buf[PATH_MAX];
    for(; i < NTIMES; ++i){
        if(mkdir("t", RWX)){
            err_sys("loop: %ld, create directory test failed\n", i);
            break;
        }
        if(chdir("t")){
            err_sys("cann't change dir to test\n");
            break;
        }
        // char *path = getcwd(buf, PATH_MAX-1);
        // if(path == NULL){
        //     printf("path: %s\n", path);
        // }else{
        //     printf("get path failed, ret = %s\n", strerror(errno));
        // }
    }

    return 0;
}