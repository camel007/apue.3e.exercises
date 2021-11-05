#include "apue.h"
#include <stdio.h>
#include <string.h>

int my_read(void* fp, char *buf, int size);
int my_write(void *fp, const char *buf, int size);
fpos_t my_seek(void *fp, fpos_t size, int whence);
int my_close(void *fp);

FILE	*funopen(const void *,
                 int (* _Nullable)(void *, char *, int),
                 int (* _Nullable)(void *, const char *, int),
                 fpos_t (* _Nullable)(void *, fpos_t, int),
                 int (* _Nullable)(void *));

FILE *my_fmemopen(void *restrict buf, size_t size, const char *restrict type){
    return funopen(buf, my_read, my_write, my_seek, my_close);
}

int main(void) {

    char *buffer = malloc(BUFSIZ);
    memset(buffer, 0, BUFSIZ);
    FILE* fp = my_fmemopen(buffer, BUFSIZ, "w");

    const char *str = "12345";
    fwrite(str, sizeof(char), strlen(str)+1, fp);
    fflush(fp);
    printf("buffer: %s\n", buffer);
    fclose(fp);

	return 0;
}

int my_read(void *fp, char *buf, int size){
    memcpy(buf, fp, size);

    return size;
}

int my_write(void *fp, const char *buf, int size) {
    printf("buf: %s\n", buf);
    memcpy(fp, buf, sizeof(char) * size);
    printf("fp: %s\n",fp);
    return size;
}

fpos_t my_seek(void *fp, fpos_t size, int whence){
    fp = fp += size;
    return 0;
}

int my_close(void *fp){
    free(fp);
}