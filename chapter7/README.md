## 7.3. Is there any way for a function that is called by main to examine the command-line arguments without (a) passing argc and argv as arguments from main to the function or (b) having main copy argc and argv into global variables?  

ex7_3.c  

## 7.4. Some UNIX system implementations purposely arrange that, when a program is executed, location 0 in the data segment is not accessible. Why?  

## 7.5. Use the typedef facility of C to define a new data type Exitfunc for an exit handler. Redo the prototype for atexit using this data type.  

```C++
typedef void(*ExitFunc)(void); 
int atexit(ExitFunc);
```

## 7.6. If we allocate an array of longs using calloc, is the array initialized to 0? If we allocate an array of pointers using calloc, is the array initialized to null pointers?  

ex7_6.c  

## 7.7. In the output from the size command at the end of Section 7.6, why aren’t any sizes given for the heap and the stack?  

堆和栈都是在运行过程中动态分配的  

## 7.8. In Section 7.7, the two file sizes (879443 and 8378) don’t equal the sums of their respective text and data sizes. Why?  

除了.text, .data, .bss还有其他区域  

## 7.9. In Section 7.7, why does the size of the executable file differ so dramatically when we use shared libraries for such a trivial program?  

static编译，会把所有依赖库都编译到可执行文件中   

## 7.10. At the end of Section 7.10, we showed how a function can’t return a pointer to an automatic variable. Is the following code correct?  
```c++
int
    f1(int val)
    {
        int num=0; int *ptr = &num;
        if (val == 0) {
            int     val;
            val = 5;
            ptr = &val; 
        }
        return(*ptr + 1);
    }
```
if语句内的val屏蔽了外层的val，但是在退出if语句后，其内部的val从栈上释放，所以*ptr可能访问到无效的值  

