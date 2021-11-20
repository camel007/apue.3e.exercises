# chapter 8 Process Control  

## 8.4 vfork function  

vfork和fork不同的点是vfork不完全拷贝父进程的地址空间到子进程中，注意这里的不完全，那就是拷贝了一些，结合本节结束提到的文件描述符和流，文件描述符是拷贝了副本的，流是共享的，参考ex_81.c  

## 8.11. Set USER ID and Set Group ID  

[深刻理解——real user id, effective user id, saved user id in Linux](https://blog.csdn.net/fmeng23/article/details/23115989)  

set_user_id 是一个标志位, saved_set_user_id是一个进程id  

## 8.12 解释器脚本  

