#include "apue.h"
#include <fcntl.h>
#include <unistd.h>

#define RWRWRW (S_IRUSR | S_IWUSR | S_IWGRP | S_IRGRP | S_IROTH | S_IWOTH)
#define SIZE 1024

void creat_file_with_hole(){
    int fd;
    if((fd = creat("file.hole", FILE_MODE)) < 0){
        err_sys("create file.hole fail");
    }

    char buf1[] = {"qwertyuiop"};
    char buf2[] = {"QWERTYUIOP"};
    if(write(fd,buf1, 10 ) != 10){
        err_sys("buf1 write error");
    }

    if(lseek(fd, 16384, SEEK_SET) == -1){
        err_sys("lseek error");
    }

    if(write(fd, buf2, 10) != 10){
        err_sys("buf2 write error");
    }
    close(fd);
}

int main(int argc, const char *argv[]){
    
    if(argc != 3) {
        printf("usage: %s source dst\n", argv[0]);
        return 0;
    }

    extern int errno;

    const char *source = argv[1];
    const char *dst = argv[2];

    int src_fd = open(source, O_RDONLY);
    if(src_fd == -1){
        err_sys("open source fail");
        return 0;
    }

    umask(0);
    int dst_fd = creat(dst, RWRWRW);
    if(dst_fd == -1){
        err_sys("creat dst file error\n");
    }

    off_t marker = 0, cur = 0;

    marker = lseek(src_fd, cur, SEEK_HOLE);

    if(marker > cur){
        // begin with data
        lseek(src_fd, cur, SEEK_SET);
    }else{
        // begin with hole
        marker = lseek(src_fd, cur, SEEK_DATA);
        lseek(dst_fd, marker, SEEK_SET);
        cur = marker;
        marker = lseek(src_fd, cur, SEEK_HOLE);
    }

    int next_data = 1;
    char buf[SIZE];
    while(cur < marker){
        size_t data_size = marker - cur;
        size_t copy_len = 0;
        if(data_size > SIZE){
            copy_len = SIZE;
        }else{
            copy_len = marker - cur;
            next_data = 0;
        }
        ssize_t r_len = read(src_fd, (void*)buf, copy_len);
        if(r_len == -1){
            printf("read source file error, %s\n", strerror(errno));
            goto final;
        }
        ssize_t w_len = write(dst_fd, (void*)buf, r_len);
        if(w_len == -1 || w_len != r_len){
            printf("write dst file error, %s\n", strerror(errno));
            goto final;
        }
        cur += r_len;
        if(next_data == 0){
            cur = lseek(src_fd, cur, SEEK_DATA);
            lseek(dst_fd, cur, SEEK_SET);
            marker = lseek(src_fd, cur, SEEK_HOLE);}
    }

final:
    close(src_fd);
    close(dst_fd);

    exit(0);
}