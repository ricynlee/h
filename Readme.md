# eitch, aka **h**
&copy; 2017 李锐森

## 一句话介绍

跨平台的命令行16进制编辑器。
> 跨平台指支持Windows/Linux，Mac还是不要命令行了.

> 仅适用于32位Windows/Linux.  
> 使用gcc或mingw(TDM-GCC)编译.  
> 未来可能兼容MSVC编译.  

## 短期计划

* 命令行定稿
* ~~设计一套适用于常数的HEX运算规则(准脚本?)~~
  > 放弃了支持这个想法,对于没有经验的我,设计一套用户友好的运算规则并不容易,而且公司加班太严重,没有时间做这种费脑子的事情

  > 本程序将仅仅支持简单的命令行HEX编辑

## 笔记
Linux下,在CFLAGS开启-std=c99时,会警告implicit declaration 'truncate64'/'truncate',但是可以成功编译,似乎可以正常执行.  
> 标准的选择会影响编译时的一系列宏定义,包括**feature test宏**.而这些宏又*可能*影响POSIX函数/GNU扩展函数的实现.`truncate`就是一个会受影响的函数.本程序使用-std=gnu99可以完全正常使用.
