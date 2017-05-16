#include "file.h"

// 判断文件是否过大
// int is_file_too_large(const char* pathname);
// 返回值:0文件大小OK,1文件过大,(-1)文件无法访问
// 若无LFS,2GB以上文件即过大;开启LFS后
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
