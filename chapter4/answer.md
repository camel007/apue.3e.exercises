# chapter 4 exercises  

## 4.1 Modify the program in Figure 4.3 to use stat instead of lstat. What changes if one of the command-line arguments is a symbolic link?  

symbolic link会被认为是regular file  

## 4.2 What happens if the file mode creation mask is set to 777 (octal)? Verify the results using your shell’s umask command  

可以创建一个文件权限为的文件如下：  
*----------   1 zhangyao  SENSETIME\Domain Users     0B 10 20 22:12 bar*   

## 4.3 Verify that turning off user-read permission for a file that you own denies your access to the file.

ex4_3.c  

## 4.4 Run the program in Figure 4.9 after creating the files foo and bar. What happens?  

creat以只写权限打开文件，如果foo, bar不具有写权限，会提示：“Permission denied”  
如果foo, bar有写权限，则不创建新文件，原有的权限也不会改变  

## 4.5  In Section 4.12, we said that a file size of 0 is valid for a regular file. We also said that the st_size field is defined for directories and symbolic links. Should we ever see a file size of 0 for a directory or a symbolic link?  

4.14节文件系统中有介绍  
在文件系统中，目录项保存的是文件名和i-node的编号，所以不可能是0  
symbolic link的大小是符号指向的文件的名字的长度，不管实际指向的文件是否存在  

## 4.6 Write a utility like cp(1) that copies a file containing holes, without writing the bytes of 0 to the output file.  
 
OSX 不知道怎么启动SEEK_HOLE， SEEK_DATA，ex4_6.c暂无调试  
