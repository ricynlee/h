#include <stdio.h>
#include <string.h>

#define HELP_MSG \
"# 支持的命令行概览\n" \
"\n" \
"* h version\n" \
"* h help\n" \
"* h file ... print ...\n" \
"* h file ... replace ...\n" \
"* h file ... delete ...\n" \
"* h file ... insert ...\n" \
"\n" \
"# 详细\n" \
"\n" \
"* version\n" \
"  > 显示版本信息\n" \
"\n" \
"* help\n" \
"  > 显示命令行帮助\n" \
"\n" \
"* file <FILENAME>\n" \
"  > 指定目标文件名\n" \
"\n" \
"* print [<ADDR>] [<FORMAT>] [<ENDIAN>] [<ADDRDISP>] [<COLORDISP>] [<PAGEDDISP>]\n" \
"  > 指定格式显示目标文件内容\n" \
"  * <ADDR>: @<start>[,<len>] | @<start>-<end>\n" \
"    * <start> <len> <end>可以是无符号十进制整数,也可以是0x开头的16进制数据.\n" \
"    * 默认显示整个文件.\n" \
"    * 只指定<start>会从该地址显示到文件尾.\n" \
"  * <FORMAT>: bin1|bin8|bin16|bin32|bin64\n" \
"              oct8|oct16|oct32|oct64\n" \
"              hex8|hex16|hex32|hex64\n" \
"              int8|int16|int32|int64\n" \
"              uint8|uint16|uint32|uint64\n" \
"              fix8.d|fix16.d|fix32.d|fix64.d\n" \
"              ufix8.d|ufix16.d|ufix32.d|ufix64.d\n" \
"              float|single|double\n" \
"    * 默认<FORMAT>是\"hex8\".\n" \
"    * fix表示定点小数,十进制数\"d\"用于描述二进制小数点位置.\n" \
"  * <ENDIAN>: big|little\n" \
"  * <ADDRDISP>: addr\n" \
"    * 以表格形式显示数据,并标出地址.\n" \
"    * 默认不标出数据地址.\n" \
"  * <COLORDISP>: colorblind|background|foreground\n" \
"    * 决定相邻数据如何区别显示.\n" \
"    * \"colorblind\"表示不以颜色区分,\"foreground\"表示以前景色区分,\"background\"表示以背景色区分.\n" \
"    * 默认的<COLORDISP>是\"colorblind\".\n" \
"  * <PAGEDDISP>: paged\n" \
"    * 决定数据是否分页显示.\n" \
"    * 默认不分页显示.\n" \
"\n" \
"* replace <ADDR> <DATA>\n" \
"* replace <ADDR> <FILENAME> [<FILEADDR>]\n" \
"  > 覆写目标文件的部分数据,尽量原地操作\n" \
"  * <ADDR>: @<start>[,<len>] | @<start>-<end>\n" \
"    * 定义要被替换的数据段.\n" \
"    * 只指定<start>会替换该地址到文件尾的所有数据.\n" \
"  * <DATA>: <byte> ... <byte>\n" \
"    * <byte>是空格分割的十六进制数据(不带0x前缀).\n" \
"  * <FILENAME>: <filename>\n" \
"    * 指定要替换的数据源文件名.\n" \
"  * <FILEADDR>: @<start>[,<len>] | @<start>-<end>\n" \
"    * 定义要用于替换的源文件数据段.\n" \
"    * 默认将整个文件用来替换.\n" \
"    * 只指定<start>,则源文件数据段是从该地址到源文件尾的所有数据.\n" \
"\n" \
"* delete <ADDR>\n" \
"  > 删除目标文件的一部分,尽量原地操作\n" \
"  * <ADDR>: @<start>[,<end>] | @<start>-<end>\n" \
"    * 指定要删除的目标文件数据段.\n" \
"    * 只指定<start>会将该地址到文件尾的数据全部删除.\n" \
"\n" \
"* insert <LOCATOR> <DATA>\n" \
"* insert <LOCATOR> <FILENAME> [<FILEADDR>]\n" \
"  > 向目标文件中插入数据,尽量原地操作\n" \
"  * <LOCATOR>: @<start>\n" \
"    * 指定要插入数据的首地址.\n" \
"    * \"@head\"表示插入到文件头,\"@tail\"表示插入到文件尾.\n" \
"  * <DATA>: <byte> ... <byte>\n" \
"  * <FILENAME>: <filename>\n" \
"    * 指定要插入的数据源文件.\n" \
"  * <FILEADDR>: @<start>[,<len>] | @<start>-<end>\n" \
"    * 定义要用于插入的源文件数据段.\n" \
"    * 默认插入整个文件.\n" \
"    * 只指定<start>,则源文件数据段是从该地址到源文件尾的所有数据.\n"

// 解析命令行参数
int parse(int argc, char* argv[]){
    for(int i=0;i<argc;i++){
        // strcmp(argv[i],"--");
    }
    return 0;
}

// 显示帮助信息(Horizontal & vertical scrollable)
int prn_help_msg(void){
    
}

int main(int argc, char* argv[]){
    printf(HELP_MSG);
    return 0;
}