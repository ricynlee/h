#ifndef _H_FILE_H
#define _H_FILE_H

// 本头文件与stdint.h有冲突
#ifdef _STDIN_H
# error("Conflicts with stdint.h even if you think it compiles.")
#endif

//
// Large file support (LFS) switch
//
#define _SUPPORT_LARGE_FILE 1

//
// LFS
//
#if _SUPPORT_LARGE_FILE
# define _FILE_OFFSET_BITS 64
#endif

#if defined(_WIN32)
# include <io.h>
# include <fcntl.h>
# if _SUPPORT_LARGE_FILE
#   define lseek   _lseeki64
    typedef off64_t offset_t;
# else
#   define lseek   _lseek
    typedef off_t   offset_t;
# endif // _SUPPORT_LARGE_FILE
#elif defined(__linux__)
# include <unistd.h>
# include <fcntl.h>
  typedef   off_t   offset_t;
#endif

#define seek lseek

//
// Function declarations
//

/*
 * 本头文件提供了POSIX几乎完全一致的文件操作,如
 * open
 * close
 * seek
 * read
 * write
 * 经过本头文件的封装,MINGW/GCC的文件读写代码可以直接移植,
 * 并可以很方便地实现32位操作系统下的LFS.
 *
 * NOTICE File offset type is offset_t instead of off_t
 * NOTICE offset is 64-bit, yet rw buffer is 32-bit on 32-bit OS's
 */

#endif // _H_FILE_H