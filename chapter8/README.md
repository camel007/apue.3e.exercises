## 8.1. In Figure 8.3, we said that replacing the call to _exit with a call to exit might cause the standard output to be closed and printf to return −1. Modify the program to check whether your implementation behaves this way. If it does not, how can you simulate this behavior?   

ex8_1.c  

## 8.2. Recall the typical arrangement of memory in Figure 7.6. Because the stack frames corresponding to each function call are usually stored in the stack, and because after a vfork the child runs in the address space of the parent, what happens if the call to vfork is from a function other than main and the child does a return from this function after the vfork? Write a test program to verify this, and draw a picture of what’s happening.  

ex8_2.c

### 使用fork
子进程拷贝了父进程的空间，包括栈，子进程如果中途不退出，也就是没有exit，在栈返回的时候也会继续执行main函数
- 没有在子进程中exit,且没有waitpid，执行结果如下：
```
first main pid = 35484, ppid=52444
before fork
begin fork function pid = 35484,ppid = 52444
var 6
end fork function pid = 35484,ppid = 52444
after fork
second main pid = 35484, ppid=52444
before normal
normal function pid = 35484,ppid = 52444
after normal
child process pid = 35485,ppid = 1
var 7
end fork function pid = 35485,ppid = 1
after fork
second main pid = 35485, ppid=1
before normal
normal function pid = 35485,ppid = 1
after normal
```
- 子进程没有exit, 有waitpid，执行输出内容和上一条一样，但是顺序不一样了，原因是加了waitpid后能确保子进程先执行,执行结果如下：  
```
first main pid = 36554, ppid=52444
before fork
begin fork function pid = 36554,ppid = 52444
child process pid = 36555,ppid = 36554
var 7
end fork function pid = 36555,ppid = 36554
after fork
second main pid = 36555, ppid=36554
before normal
normal function pid = 36555,ppid = 36554
after normal
var 6
end fork function pid = 36554,ppid = 52444
after fork
second main pid = 36554, ppid=52444
before normal
normal function pid = 36554,ppid = 52444
after normal
```
- 在子进程中exit, 没有waitpid，不会执行main函数中的normal fuction了，中途已经退出了，执行结果如下：  
```
first main pid = 35862, ppid=52444
before fork
begin fork function pid = 35862,ppid = 52444
var 6
end fork function pid = 35862,ppid = 52444
after fork
second main pid = 35862, ppid=52444
before normal
normal function pid = 35862,ppid = 52444
after normal
child process pid = 35863,ppid = 1
```
- 在子进程中使用exit,有waitpid，也不会执行main函数了(原理和上一条一样，只是子进程和父进程的执行顺序不一样了)，执行结果如下：
```
first main pid = 36241, ppid=52444
before fork
begin fork function pid = 36241,ppid = 52444
child process pid = 36242,ppid = 36241
var 6
end fork function pid = 36241,ppid = 52444
after fork
second main pid = 36241, ppid=52444
before normal
normal function pid = 36241,ppid = 52444
after normal
```

### 使用vfork  
vfork的子进程在没有exec之前在父进程空间中执行,如果到退出都没有exec，子进程会破坏父进程的数据  
- 没有在子进程中exit,且没有waitpid，执行结果如下：
```
first main pid = 38662, ppid=52444
before fork
begin fork function pid = 38662,ppid = 52444
child process pid = 38663,ppid = 38662
end fork function var = 7, pid = 38663,ppid = 38662
after fork
second main pid = 38663, ppid=38662
  1 #include "apue.h"
before normal
normal function pid = 38663,ppid = 38662
after normal
end fork function var = 0, pid = 38662,ppid = 52444
begin fork function pid = 38662,ppid = 52444
child process pid = 38664,ppid = 38662
end fork function var = 7, pid = 38664,ppid = 38662
end fork function var = 7, pid = 38662,ppid = 52444
[1]    38662 segmentation fault  ./ex8_2
```
- 在上一条的基础上加一个execl，输出如下：  
```
first main pid = 38967, ppid=52444
before fork
begin fork function pid = 38967,ppid = 52444
child process pid = 38969,ppid = 38967
end fork function var = 7, pid = 38967,ppid = 52444
after fork
second main pid = 38967, ppid=52444
before normal
normal function pid = 38967,ppid = 52444
after normal
CMakeCache.txt          a.out                   ex8_1                   sample8_12              sample8_23              t.cpp
CMakeFiles		cmake_install.cmake	ex8_2			sample8_16		sample8_30
Makefile		echoall			getpwduid		sample8_20		sample8_6
```

## 8.3. Rewrite the program in Figure 8.6 to use waitid instead of wait. Instead of calling pr_exit, determine the equivalent information from the siginfo structure.  

## 8.4. 
```
When we execute the program in Figure 8.13 one time, as in  
$./a.out
the output is correct. But if we execute the program multiple times, one right after the other, as in
$ ./a.out ; ./a.out ; ./a.out output from parent
ooutput from parent ouotuptut from child
        put from parent
        output from child
        utput from child
the output is not correct. What’s happening? How can we correct this? Can this problem happen if we let the child write its output first?
```  

结束信号被其他进程捕获了，所以才有打印错乱   
如果子进程先走，不会发生这种事情，因为TELL_PARENT的时候会写具体tell那个子进程的父进程，不会tell到其他进程中   

## 8.5. In the program shown in Figure 8.20, we call execl, specifying the pathname of the interpreter file. If we called execlp instead, specifying a filename of testinterp, and if the directory /home/sar/bin was a path prefix, what would be printed as argv[2] when the program is run?  

ex8_5.c  

## 8.6. Write a program that creates a zombie, and then call system to execute the ps(1) command to verify that the process is a zombie.  

ex8_6.c  

## 8.7. We mentioned in Section 8.10 that POSIX.1 requires open directory streams to be closed across an exec. Verify this as follows: call opendir for the root directory, peek at your system’s implementation of the DIR structure, and print the close-on-exec flag. Then open the same directory for reading, and print the close-on-exec flag.  

