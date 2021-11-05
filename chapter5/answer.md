# chapter 5 exercises  

## 5.1 Implement setbuf using setvbuf.    

参考ex5_1.c  

## 5.2 Type in the program that copies a file using line-at-a-time I/O (fgets and fputs) from Figure 5.5, but use a MAXLINE of 4. What happens if you copy lines that exceed this length? Explain what is happening. 

会分两次读取，每次读三个字符+null,下一次继续读该行，知道遇到EOF,参考ex5_2.c    

## 5.3 What does a return value of 0 from printf mean?  

没有任何字符输出  

## 5.4 The following code works correctly on some machines, but not on others. What could be the problem?  
```C++
#include    <stdio.h>
int main(void)
{
        char c;
        while ((c = getchar()) != EOF)
        putchar(c);
}
```
getchar返回下一个字符时，将unsigned char转换为int，要求返回值是int的原因是，可以返回所有可能的字符再加上一个已出错或者到达文件尾端的指示.

**暂时不知道为什么在什么机器上出错，为什么出错？**

## 5.5 How would you use the fsync function (Section 3.13) with a standard I/O stream?  

ex5_5.c  

## 5.6 In the programs in Figures 1.7 and 1.10, the prompt that is printed does not contain a newline, and we don’t call fflush. What causes the prompt to be output?  

缓冲区切换, ex5_6.c  

## 5.7 BSD-based systems provide a function called funopen that allows us to intercept read, write, seek, and close calls on a stream. Use this function to implement fmemopen for FreeBSD and Mac OS X  

ex5_7.c