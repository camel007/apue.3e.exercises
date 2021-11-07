## 6.1. If the system uses a shadow file and we need to obtain the encrypted password, how do we do so?  

## 6.2. If you have superuser access and your system uses shadow passwords, implement the previous exercise.

## 6.3. Write a program that calls uname and prints all the fields in the utsname structure. Compare the output to the output from the uname(1) command.

ex6_3.c  
`uname -p` is the extension of the standard  

## 6.4. Calculate the latest time that can be represented by the time_t data type. After it wraps around, what happens?  

```c++
typedef long                    __darwin_time_t;        /* time() */
typedef __darwin_time_t         time_t;
```
64位机器,long占用8个字节,最大值为0x7FFFFFFFFFFFFFFF，下一秒进入0x100000000000000000,就是1970.01.01 00:00:00减去0x100000000000000000这个时间

ex6_4.c 会溢出

## 6.5. Write a program to obtain the current time and print it using strftime, so that it looks like the default output from date(1). Set the TZ environment variable to different values and see what happens.  

ex6_4.c  
```shell
export TZ=Asia/Shanghai
2021年11月 7日 星期日 20时12分03秒 CST

export TZ=Asia/Tokyo
2021年11月 7日 星期日 21时12分14秒 JST
```