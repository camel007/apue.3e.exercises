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

## 4.7 Note in the output from the ls command in Section 4.12 that the files core and core.copy have different access permissions. If the umask value didn’t change between the creation of the two files, explain how the difference could have occurred  

core文件为creat或者Open创建的，可以额外指定权限位，生成core.copy的时候只生效umask屏蔽字，所以会改变core.copy的权限  

## 4.8 When running the program in Figure 4.16, we check the available disk space with the df(1) command. Why didn’t we use the du(1) command?  

Linux du （英文全拼：disk usage）命令用于显示目录或文件的大小。  
Linux df（英文全拼：disk free） 命令用于显示目前在 Linux 系统上的文件系统磁盘使用情况统计。  

## 4.9 In Figure 4.20, we show the unlink function as modifying the changed-status time of the file itself. How can this happen?  

i-node包含指向数据块的指针， unlink一个文件会同步删除对应的i-node中的指向数据块的指针，根据书中介绍状态更改时间为该文件i-node最后一次被修改的时间  

## 4.10 In Section 4.22, how does the system’s limit on the number of open files affect the myftw function?  

影响递归深度  

## 4.11 In Section 4.22, our version of ftw never changes its directory. Modify this routine so that each time it encounters a directory, it uses the chdir function to change to that directory, allowing it to use the filename and not the pathname for each call to lstat. When all the entries in a directory have been processed, execute chdir(".."). Compare the time used by this version and the version in the text.  

ex4_11.c

## 4.12 Each process also has a root directory that is used for resolution of absolute pathnames. This root directory can be changed with the chroot function. Look up the description for this function in your manuals. When might this function be useful?  

https://man7.org/linux/man-pages/man2/chroot.2.html  

## 4.13 How can you set only one of the two time values with the utimes function?  

用stat保存访问时间和修改时间的其中一个，只设置另一个  

ex4_13.c_bak  macos的stat函数和linux不一样，没有st_atim的函数  

## 4.14 Some versions of the finger(1) command output ‘‘New mail received ...’’ and ‘‘unread since ...’’ where ... are the corresponding times and dates. How can the program determine these two times and dates?  

从文件的状态修改时间，访问时间和修改时间来决定的  

## 4.15 Examine the archive formats used by the cpio(1) and tar(1) commands. (These descriptions are usually found in Section 5 of the UNIX Programmer’s Manual.) How many of the three possible time values are saved for each file? When a file is restored, what value do you think the access time is set to, and why?  

## 4.16 Does the UNIX System have a fundamental limitation on the depth of a directory tree? To find out, write a program that creates a directory and then changes to that directory, in a loop. Make certain that the length of the absolute pathname of the leaf of this directory is greater than your system’s PATH_MAX limit. Can you call getcwd to fetch the directory’s pathname? How do the standard UNIX System tools deal with this long pathname? Can you archive the directory using either tar or cpio?  


在macos上尝试，深度非常深，22000+的时候给停了，我这里MAX_PATH=1024,leaf pathname肯定超过了；然后悲催的删掉这个目录很麻烦，只能chdir进一定的深度，然后删掉，然后继续删掉
tar的时候会提示错误，“tar: Error exit delayed from previous errors.”可能是深度不够  

## 4.17 In Section 3.16, we described the /dev/fd feature. For any user to be able to access these files, their permissions must be rw-rw-rw-. Some programs that create an output file delete the file first, in case it already exists, ignoring the return code:
        unlink(path);
        if ((fd = creat(path, FILE_MODE)) < 0)
err_sys(...);
What happens if path is /dev/fd/1?  

0,1,2,应该是stdin, stdout, stderr，随便删不知道会不会有问题，没尝试