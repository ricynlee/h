# eitch, aka **h**
&copy; 2017 李锐森

## 一句话介绍

跨平台的命令行16进制编辑器。
> 跨平台指支持Windows/Linux，Mac还是不要命令行了。

> 仅适用于32位Windows/Linux.  
> 使用gcc或mingw(TDM-GCC)编译.  
> 未来可能兼容MSVC编译.  

## 短期计划

Linux下,在CFLAGS开启-std=c99时,会警告implicit declaration 'truncate64'/'truncate',但是可以成功编译,似乎可以正常执行.  
找到警告原因.  
> 据称是标准C不推荐POSIX族函数?因为在开启-std=gnu99后不会有警告.
