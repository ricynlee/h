#include <stdio.h>
#include <string.h>
#include "term/term.h"
#include <malloc.h>
#include <stdlib.h>

#if defined(_WIN32)
# include <windows.h>
# include <conio.h>
#elif defined(__linux__)
# include <sys/ioctl.h>
# include <unistd.h>
# include <termios.h>
#endif

#define HELP_MSG_MAX_LINES 128
char* HELP_MSG[] = {
    "# h - A command-line hex editor",
    "",
    "* h version",
    "* h help",
    "* h file ... print ...",
    "* h file ... replace ...",
    "* h file ... delete ...",
    "* h file ... insert ...",
    "",
    "# Command-line arguments",
    "",
    "* version",
    "  > Display version information",
    "",
    "* help",
    "  > Display this help message",
    "",
    "* file <FILENAME>",
    "  > Specify the name of the file to be edited (or viewed), i.e. target file",
    "",
    "* print [<ADDR>] [<FORMAT>] [<ENDIAN>] [<ADDRDISP>] [<COLORDISP>] [<PAGEDDISP>]",
    "  > Display the file's content using specified format",
    "  * <ADDR>: @<start>[,<len>] | @<start>-<end>",
    "    * <start> <len> <end> may be unsigned dec integers, or hex integers starting with 0x.",
    "    * By default, the whole file is displayed.",
    "    * With only <start> field specified, file content between the offset and EOF is displayed.",
    "  * <FORMAT>: bin1|bin8|bin16|bin32|bin64",
    "              oct8|oct16|oct32|oct64",
    "              hex8|hex16|hex32|hex64",
    "              int8|int16|int32|int64",
    "              uint8|uint16|uint32|uint64",
    "              fix8.d|fix16.d|fix32.d|fix64.d",
    "              ufix8.d|ufix16.d|ufix32.d|ufix64.d",
    "              float|single|double",
    "    * Default <FORMAT> is,\"hex8\".",
    "    * \"fix\" stands for fixed-point decimals, and dec number \"d\" sets the decimal point.",
    "  * <ENDIAN>: big|little",
    "  * <ADDRDISP>: addr",
    "    * Addr is displayed along with data (in the form of a table).",
    "    * By default, no addr is displayed.",
    "  * <COLORDISP>: colorblind|background|foreground",
    "    * Specifies how neighboring data is distinguished.",
    "    * \"colorblind\" stands for no distinguishment using color, \"foreground\" for forground color, and \"background\" for background color.",
    "    * By default <COLORDISP> is \"colorblind\".",
    "  * <PAGEDDISP>: paged",
    "    * Specifiy if data is displayed page by page.",
    "    * Not paged by default.",
    "",
    "* replace <ADDR> <DATA>",
    "* replace <ADDR> <FILENAME> [<FILEADDR>]",
    "  > Rewrite part of target file. In-place if possible.",
    "  * <ADDR>: @<start>[,<len>] | @<start>-<end>",
    "    * Specify data segment to be replaced.",
    "    * With only <start> specified, all data after this offset will be replaced.",
    "  * <DATA>: <byte> ... <byte>",
    "    * <byte> is an octet in hex form(w/o 0x prefix).",
    "  * <FILENAME>: <filename>",
    "    * Specified the replacing source file.",
    "  * <FILEADDR>: @<start>[,<len>] | @<start>-<end>",
    "    * Specify replacing data segment in the source file.",
    "    * By default the whole file is used.",
    "    * With only <start> specified, replacing data segment is all data after this offset.",
    "",
    "* delete <ADDR>",
    "  > Remove part of the target file. In-place if possible.",
    "  * <ADDR>: @<start>[,<end>] | @<start>-<end>",
    "    * Specify data segment to be removed in the target file.",
    "    * With only <start> specified, all data after this offset will be removed.",
    "",
    "* insert <LOCATOR> <DATA>",
    "* insert <LOCATOR> <FILENAME> [<FILEADDR>]",
    "  > Add data to the target file. In-place if possible.",
    "  * <LOCATOR>: @<start>",
    "    * Specify the initial address of inserted data in the target file.",
    "    * \"@head\" stands for offset 0, \"@tail\" for EOF.",
    "  * <DATA>: <byte> ... <byte>",
    "  * <FILENAME>: <filename>",
    "    * Specify a source file to be inserted to the target file.",
    "  * <FILEADDR>: @<start>[,<len>] | @<start>-<end>",
    "    * Specify the data segment in the in the source file to be inserted.",
    "    * By default the whole source file is inserted.",
    "    * With only <start> specified, all data in the source file after this offset will be inserted."
};

// 解析命令行参数
int parse(int argc, char* argv[]){
    for(int i=0;i<argc;i++){
        // strcmp(argv[i],"--");
    }
    return 0;
}

// Private enum for get_arrow_key
typedef enum{
    AK_EXCEPT       = -1,
    AK_NON_ARROW    = 0,
    
    AK_UP,
    AK_DOWN,
    AK_LEFT,
    AK_RIGHT,
    
    AK_BUTT
}ARROW_KEY;

// Suspend the process, until a key is pressed
static int get_arrow_key(void){
#if defined(_WIN32)
    if(getch() == 224){
        switch(getch()){
        case 72:
            return AK_UP;
        case 80:
            return AK_DOWN;
        case 75:
            return AK_LEFT;
        case 77:
            return AK_RIGHT;
        default:
            return AK_NON_ARROW;
        }
    }else{
        return AK_NON_ARROW;
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
                    return AK_UP;
                case 'B':
                    return AK_DOWN;
                case 'D':
                    return AK_LEFT;
                case 'C':
                    return AK_RIGHT;
                default:
                    return AK_NON_ARROW;
            }
        }else{
            return AK_NON_ARROW;
        }
    }else{
        return AK_NON_ARROW;
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &tios);
#endif
    
    return AK_EXCEPT;
}

#define MIN(x,y) ((x)<(y)?(x):(y))
#define MAX(x,y) ((x)>(y)?(x):(y))
// 显示帮助信息(Horizontal & vertical scrollable with arrow keys)
void prn_help_msg(void){
    int max_x = 0, max_y = sizeof(HELP_MSG)/sizeof(char*)-1; // Size of HELP_MSG
    for(int i=0; i<=max_y; i++){
        tmp_x = MAX(strlen(HELP_MSG[i])-1, max_x);
    }

    int tsz_x, tsz_y; // Size of current terminal/console
    int pos_x = 0, pos_y = 0; // Display origin of HELP_MSG


    while(1){ // Checking if arrow key pressed
        get_term_size(&tsz_x, &tsz_y);
        
        for(int i=pos_x; i<=max_y; i++){
            printf("%s\n", HELP_MSG[i] + MIN(strlen(HELP_MSG[i]), pos_x));
            max_x = strlen(HELP_MSG[i])-1>max_x ? strlen(HELP_MSG[i])-1 : max_x;
        }
        
        switch( get_arrow_key() ){
            case AK_UP:
                pos_y--;
                break;
            case AK_DOWN:
                pos_y++;
                break;
            case AK_LEFT:
                pos_x--;
                break;
            case AK_RIGHT:
                pos_x++;
                break;
            default:
                return;
        }
    }
}



int main(int argc, char* argv[]){
    prn_help_msg();
    return 0;
}
