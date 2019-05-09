# eitch
&copy; 2017~2019 李锐森

## 介绍

~~跨平台的命令行16进制文件阅读器.~~
本来想做一个16进制文件编辑器,后来缩水为阅读器,现在也不想做了.
但是好在
- 留下了一个封装了的类Posix文件操作库,支持大文件.
  - open
  - close
  - lseek
  - tell
  - read
  - write
  - truncate
- 留下了一个终端操作库.
  - get_term_size
  - printf_color
  - clear_term
  - get_key
  - put_cursor

> 跨平台,支持Windows/Linux.
> 使用gcc或mingw(TDM-GCC)编译.
> 重要的宏`_WIN32_USE_VTES`,`_FILE_OFFSET_BITS`.用`$CC -D`传递给编译器.详情参考代码.
> `$CFLAGS`需要(隐式或显式)包含`-m32`.

***

## Brief

Eitch was intended to be a **h**ex editor, and this is how eitch got its name \(h\). Then it was trimmed to a hex viewer. Now it's given up. But after all it is still
- a Posix-like file operation library that supports large files
  - open
  - close
  - lseek
  - tell
  - read
  - write
  - truncate
- a terminal operation library
  - get_term_size
  - printf_color
  - clear_term
  - get_key
  - put_cursor
 
> Linux/Windows supported
> Built with gcc or mingw (tdm-gcc)
> Predefined macros `_WIN32_USE_VTES`,`_FILE_OFFSET_BITS` are important. Pass them to compiler with `$CC -D`. Vide the code for details
> `-m32` should be (implicitly or explicitly) included in `$CFLAGS`
