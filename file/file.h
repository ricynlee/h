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
extern int is_file_too_large(const char* pathname);
# if defined(_WIN32)
extern int truncate_WIN32_API(const char* path, off_t length);
# endif

#endif // _H_FILE_H
