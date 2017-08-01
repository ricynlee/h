#include "file.h"

#if defined(_WIN32)
# include <windows.h>
# include <unistd.h>
#endif

// 判断文件是否过大
// int is_file_too_large(const char* pathname);
// 返回值:0文件大小OK,1文件过大,(-1)文件无法访问
// 若无LFS,2GB以上文件即过大
int is_file_too_large(const char* pathname){
    int     fd, ret;
    off_t   offset;
    fd=open(pathname,O_RDONLY);
    if(fd<0)
        return (-1);

    offset=lseek(fd,0,SEEK_END);
    if(offset<0){
        ret=1;
    }else{
        ret=0;
    }

    close(fd);

    return ret;
}

// Win32 API实现的truncate,功能近似POSIX truncate
// 仅支持操作本地存储器上的文件
#if defined(_WIN32)
int truncate_WIN32_API(const char* path, off_t length){

    HANDLE hF = CreateFile(path, FILE_GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_WRITE_THROUGH, NULL);
    if(INVALID_HANDLE_VALUE == hF)
        return EACCES;

# if defined(_FILE_OFFSET_BITS) && _FILE_OFFSET_BITS==64 // LFS on

#   if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    LONG length_HI_32BITS = *((LONG*)(&length) + 1);
    LONG length_LO_32BITS = *((LONG*)(&length));
#   elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    LONG length_HI_32BITS = *((LONG*)(&length));
    LONG length_LO_32BITS = *((LONG*)(&length) + 1);
#   endif

    if(INVALID_SET_FILE_POINTER == SetFilePointer(hF, length_LO_32BITS, &length_HI_32BITS, FILE_BEGIN){
        CloseHandle(hF);
        return EINVAL;
    }

# else // LFS off

    if(INVALID_SET_FILE_POINTER == SetFilePointer(hF, length, NULL, FILE_BEGIN){
        CloseHandle(hF);
        return EINVAL;
    }

# endif

    if(! SetEndOfFile(hF)){
        CloseHandle(hF);
        return EIO;
    }

    CloseHandle(hF);
    return 0;
}
#endif
