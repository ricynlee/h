#include <stdio.h>
#include <string.h>
#include "term/term.h"

#if defined(_WIN32)
# include <windows.h>
# include <conio.h>
#elif defined(__linux__)
# include <sys/ioctl.h>
# include <unistd.h>
# include <termios.h>
#endif

#define HELP_MSG \
"# h - A command-line hex editor\n" \
"\n" \
"* h version\n" \
"* h help\n" \
"* h file ... print ...\n" \
"* h file ... replace ...\n" \
"* h file ... delete ...\n" \
"* h file ... insert ...\n" \
"\n" \
"# Command-line arguments\n" \
"\n" \
"* version\n" \
"  > Display version information\n" \
"\n" \
"* help\n" \
"  > Display this help message\n" \
"\n" \
"* file <FILENAME>\n" \
"  > Specify the name of the file to be edited (or viewed), i.e. target file\n" \
"\n" \
"* print [<ADDR>] [<FORMAT>] [<ENDIAN>] [<ADDRDISP>] [<COLORDISP>] [<PAGEDDISP>]\n" \
"  > Display the file's content using specified format\n" \
"  * <ADDR>: @<start>[,<len>] | @<start>-<end>\n" \
"    * <start> <len> <end> may be unsigned dec integers, or hex integers starting with 0x.\n" \
"    * By default, the whole file is displayed.\n" \
"    * With only <start> field specified, file content between the offset and EOF is displayed.\n" \
"  * <FORMAT>: bin1|bin8|bin16|bin32|bin64\n" \
"              oct8|oct16|oct32|oct64\n" \
"              hex8|hex16|hex32|hex64\n" \
"              int8|int16|int32|int64\n" \
"              uint8|uint16|uint32|uint64\n" \
"              fix8.d|fix16.d|fix32.d|fix64.d\n" \
"              ufix8.d|ufix16.d|ufix32.d|ufix64.d\n" \
"              float|single|double\n" \
"    * Default <FORMAT> is \"hex8\".\n" \
"    * \"fix\" stands for fixed-point decimals, and dec number \"d\" sets the decimal point.\n" \
"  * <ENDIAN>: big|little\n" \
"  * <ADDRDISP>: addr\n" \
"    * Addr is displayed along with data (in the form of a table).\n" \
"    * By default, no addr is displayed.\n" \
"  * <COLORDISP>: colorblind|background|foreground\n" \
"    * Specifies how neighboring data is distinguished.\n" \
"    * \"colorblind\" stands for no distinguishment using color, \"foreground\" for forground color, and \"background\" for background color.\n" \
"    * By default <COLORDISP> is \"colorblind\".\n" \
"  * <PAGEDDISP>: paged\n" \
"    * Specifiy if data is displayed page by page.\n" \
"    * Not paged by default.\n" \
"\n" \
"* replace <ADDR> <DATA>\n" \
"* replace <ADDR> <FILENAME> [<FILEADDR>]\n" \
"  > Rewrite part of target file. In-place if possible.\n" \
"  * <ADDR>: @<start>[,<len>] | @<start>-<end>\n" \
"    * Specify data segment to be replaced.\n" \
"    * With only <start> specified, all data after this offset will be replaced.\n" \
"  * <DATA>: <byte> ... <byte>\n" \
"    * <byte> is an octet in hex form(w/o 0x prefix).\n" \
"  * <FILENAME>: <filename>\n" \
"    * Specified the replacing source file.\n" \
"  * <FILEADDR>: @<start>[,<len>] | @<start>-<end>\n" \
"    * Specify replacing data segment in the source file.\n" \
"    * By default the whole file is used.\n" \
"    * With only <start> specified, replacing data segment is all data after this offset.\n" \
"\n" \
"* delete <ADDR>\n" \
"  > Remove part of the target file. In-place if possible.\n" \
"  * <ADDR>: @<start>[,<end>] | @<start>-<end>\n" \
"    * Specify data segment to be removed in the target file.\n" \
"    * With only <start> specified, all data after this offset will be removed.\n" \
"\n" \
"* insert <LOCATOR> <DATA>\n" \
"* insert <LOCATOR> <FILENAME> [<FILEADDR>]\n" \
"  > Add data to the target file. In-place if possible.\n" \
"  * <LOCATOR>: @<start>\n" \
"    * Specify the initial address of inserted data in the target file.\n" \
"    * \"@head\" stands for offset 0, \"@tail\" for EOF.\n" \
"  * <DATA>: <byte> ... <byte>\n" \
"  * <FILENAME>: <filename>\n" \
"    * Specify a source file to be inserted to the target file.\n" \
"  * <FILEADDR>: @<start>[,<len>] | @<start>-<end>\n" \
"    * Specify the data segment in the in the source file to be inserted.\n" \
"    * By default the whole source file is inserted.\n" \
"    * With only <start> specified, all data in the source file after this offset will be inserted.\n"

// 解析命令行参数
int parse(int argc, char* argv[]){
    for(int i=0;i<argc;i++){
        // strcmp(argv[i],"--");
    }
    return 0;
}

// 显示帮助信息(Horizontal & vertical scrollable)
void prn_help_msg(void){
#if defined(_WIN32)
    if(getch() == 224){
        switch(getch()){
        case 72:
            printf("Up");
            break;
        case 80:
            printf("Down");
            break;
        case 75:
            printf("Left");
            break;
        case 77:
            printf("Right");
            break;
        default:
            break;
        }
    }
#elif defined(__linux__)
    char arrow_key_buf[3];
    struct termios tios, tios_pause;
    fflush(stdout);

    tcgetattr(STDIN_FILENO, &tios);

    tios_pause = tios;
    tios_pause.c_lflag&=~ICANON; // 关闭Canonical模式(这样无须换行即可获得输入)
    tios_pause.c_lflag&=~ECHO;   // 关闭回显
    tios_pause.c_cc[VMIN]=1;     // 在非Canonical模式下最少输入1字符即可读取
    tios_pause.c_cc[VTIME]=0;    // read会一直等待输入,无超时
    
    tcsetattr(STDIN_FILENO, TCSANOW, &tios_pause);

    if(read(STDIN_FILENO,&arrow_key_buf,sizeof(arrow_key_buf))==sizeof(arrow_key_buf)){
        if(arrow_key_buf[0] == '\033' && arrow_key_buf[1] == '['){
            switch(arrow_key_buf[2]){
                case 'A':
                    printf("Up");
                    break;
                case 'B':
                    printf("Down");
                    break;
                case 'D':
                    printf("Left");
                    break;
                case 'C':
                    printf("Right");
                    break;
            }
        }
    }
    
    tcsetattr(STDIN_FILENO, TCSANOW, &tios);
#endif
}

int main(int argc, char* argv[]){
    printf(HELP_MSG);
    return 0;
}
