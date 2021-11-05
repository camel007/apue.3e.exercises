#include "apue.h"
#include <stdio.h>

void my_setbuf(FILE *restrict fp, char *restrict buf);
void pr_stdio(const char* name, FILE *fp);
int is_unbuffered(FILE *fp);
int is_linebuffered(FILE *fp);
int is_fullbuffered(FILE *fp);
int buffer_size(FILE *fp);

int main(void) {
	
	if(getchar() == EOF)
		err_sys("getchar error");	
	fputs("one line to std error\n", stderr);
	pr_stdio("stderr", stderr);

	printf("BUFSIZ: %d\n", BUFSIZ);

	FILE *fp;
	if((fp = fopen("foo", "r")) == NULL){
		err_sys("open fail\n");
	}
	if(fgetc(fp) == EOF) {
		err_ret("empty file\n");
	}
	pr_stdio("file", fp);

	my_setbuf(fp, NULL);
	pr_stdio("file", fp);

	char *buffer = malloc(BUFSIZ);
	my_setbuf(fp, buffer);
	pr_stdio("file", fp);
	free(buffer);

	return 0;
}

void my_setbuf(FILE *restrict fp, char *restrict buf) {
	if (buf == NULL) {
		printf("null\n");
		setvbuf(fp, NULL, _IONBF, 0);
	}else{
		setvbuf(fp, buf, _IOFBF, BUFSIZ);
	}
}

void
pr_stdio(const char *name, FILE *fp)
{
    printf("stream = %s, ", name);
    if (is_unbuffered(fp))
        printf("unbuffered");
    else if (is_linebuffered(fp))
        printf("line buffered");
    else /* if neither of above */
        printf("fully buffered");
    printf(", buffer size = %d\n", buffer_size(fp));
}


#if defined(_IO_UNBUFFERED)
int
is_unbuffered(FILE *fp)
{
    return(fp->_flags & _IO_UNBUFFERED);
}
int
is_linebuffered(FILE *fp)
{
    return(fp->_flags & _IO_LINE_BUF);
}
int
buffer_size(FILE *fp)
{
    return(fp->_IO_buf_end - fp->_IO_buf_base);
}
#elif defined(__SNBF)
int
is_unbuffered(FILE *fp)
{
    return(fp->_flags & __SNBF);
}

int
is_linebuffered(FILE *fp)
{
    return(fp->_flags & __SLBF);
}
int
buffer_size(FILE *fp)
{
    return(fp->_bf._size);
}
#elif defined(_IONBF)
#ifdef _LP64
#define _flag __pad[4]
#define _ptr __pad[1]
#define _base __pad[2]
#endif
int
is_unbuffered(FILE *fp)
{
    return(fp->_flag & _IONBF);
}
int
is_linebuffered(FILE *fp)
{
    return(fp->_flag & _IOLBF);
}

int
buffer_size(FILE *fp)
{
#ifdef _LP64
    return(fp->_base - fp->_ptr);
#else
    return(BUFSIZ); /* just a guess */
#endif
}
#else
#error unknown stdio implementation!
#endif
