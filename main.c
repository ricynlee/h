#include <stdio.h>
#include "term.h"
#include "file.h"

#define FILE_4GBPLUS    "../Backup/Storage/Softwares/Windows/Sci_Eng_Dev/FPGA_Dev/Vivado_with_lic/Xilinx_Vivado_SDK_Win_2015.3_0929_1.tar.gz"
#define FILE_2GBPLUS    "../Backup/Storage/Softwares/Windows/Sys_Tools/OS/InstCD/cn_windows_7_ultimate_with_sp1_x64_dvd_618537.iso"
#define FILE_1GBPLUS    "../Backup/Storage/Softwares/Windows/Sci_Eng_Dev/MATLab/Matlab_r2007b_Win32_Key_Incl.rar"
#define FILE_NORMALSIZE "../Backup/Storage/Softwares/Windows/Multimedia_Web/VectorMagicSetup_Keygen_incl.7z"
#define FILE_ZEROSIZE   "../empty"
#define FILE_NONEXIST   "../nonexist"
#define FILE_NOACCESS   "../pagefile.sys"


int main(){
    int w,h;
    get_term_size(&w,&h);
    printf_color(FC_RED,BC_CYAN,  "width:%d",w);
    printf_color(FC_DEFAULT,BC_DEFAULT," ");
    printf_color(FC_RED,BC_SILVER,"height:%d\n",h);

    printf("%s %d\n","FILE_4GBPLUS   ",is_file_too_large(FILE_4GBPLUS   ));
    printf("%s %d\n","FILE_2GBPLUS   ",is_file_too_large(FILE_2GBPLUS   ));
    printf("%s %d\n","FILE_1GBPLUS   ",is_file_too_large(FILE_1GBPLUS   ));
    printf("%s %d\n","FILE_NORMALSIZE",is_file_too_large(FILE_NORMALSIZE));
    printf("%s %d\n","FILE_ZEROSIZE  ",is_file_too_large(FILE_ZEROSIZE  ));
    printf("%s %d\n","FILE_NONEXIST  ",is_file_too_large(FILE_NONEXIST  ));
    printf("%s %d\n","FILE_NOACCESS  ",is_file_too_large(FILE_NOACCESS  ));
    
    int fd=open(FILE_4GBPLUS,O_RDONLY);
    lseek(fd,5LL<<30,SEEK_SET);
    
    printf("off_t size:%d\n",sizeof(off_t));
    
    unsigned char c;
    for(int i=0;i<16;i++){
        printf("%016llx:",tell(fd));
        read(fd,&c,1);
        printf("%02x\n",c);
    }
    close(fd);
    
    pause();

    return 0;
}
