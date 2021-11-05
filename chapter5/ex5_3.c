#include <stdio.h>
#include "apue.h"

int main(void)
{
        char c;
        while ((c = getchar()) != EOF)
        putchar(c);
        if(ferror(stdin)){
            err_sys("input error");
        }
}