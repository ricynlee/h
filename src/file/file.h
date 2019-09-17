/*
Copyright (c) 2017 ricynlee

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */

#ifndef _H_FILE_H
#define _H_FILE_H

# include <unistd.h>
# include <fcntl.h>

//
// Large file support (LFS)
// 在CFLAGS里添加-D_FILE_OFFSET_BITS=64以启用LFS
# if defined(_WIN32) // WIN32
#   if defined(_FILE_OFFSET_BITS) && _FILE_OFFSET_BITS==64
#     define lseek    _lseeki64
#     define tell     _telli64
#     define off_t    off64_t
#   endif
#   define truncate   truncate_WIN32_API
# elif defined(__linux__) // LINUX
#   if defined(_FILE_OFFSET_BITS) && _FILE_OFFSET_BITS==64 && __STDC_VERSION__>=199901L
#     define truncate truncate64 // Weird. Def necessary only when -std=c99 enabled.
#   endif
#   define tell(fd)   lseek(fd,0,SEEK_CUR)
# endif

//
// Function declarations
//
/*
 * 本头文件提供了POSIX文件操作函数,如
 * open
 * close
 * lseek
 * tell
 * read
 * write
 * truncate
 * 经过本头文件的封装,MINGW/GCC的文件读写代码可以直接移植,
 * 并可以很方便地实现32位操作系统下的LFS.
 *
 * NOTICE only offset is 64-bit
 */
extern int access_test(const char* path);
# if defined(_WIN32)
extern int truncate_WIN32_API(const char* path, off_t length);
# endif

#endif // _H_FILE_H
