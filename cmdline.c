/*
 * version
    显示版本信息

 * help
    显示帮助

文件模式
 * file <FILENAME>
    指定目标文件名

 * print [<ADDR>] [<FORMAT>] [<ENDIAN>] [<BITWIDTH>] [<LABELDISP>] [<COLORDISP>] [<PAGEDDISP>]
    指定格式显示目标文件内容
    <ADDR>: @<start>[,<len>] | @<start>-<end>
     * <start> <len> <end> 可以是十进制整数,也可以是0x开头的16进制数据.
     * 默认显示整个文件.
    <FORMAT>: bin|oct|hex|dec[,signed]|dec,unsigned|fixed[,signed]|fixed,unsigned|float
     * 默认 <FORMAT> 是 "hex".
    <ENDIAN>: big|little
    <BITWIDTH>: <bitwidth>[.<decimalplace>]
     * <bitwidth> 可以是 1,8,16,32,64
     * 其中1仅适用于<FORMAT>是"bin"的情况.
     * 当<FORMAT>是"float"时, 只可选择32或64.默认<bitwidth>是8.
     * <decimalplace>仅当<FORMAT>是"fixed"启用. 默认<decimalplace>是0.
    <ADDRDISP>: addr:on|off
     * 默认<ADDRDISP>是"on".
    <COLORDISP>: color:blind|color:background|color:foreground
     * 决定相邻数据如何区别显示. 默认的 <COLORDISP> 是 "colorblind".
    <PAGEDDISP>: paged:on|off
     * 决定数据是否分页显示,默认开启.

 * replace <START> <DATA>
 * replace <ADDR> <FILENAME> [<ADDR_SRC>]
    等长覆写目标文件的部分数据,原地操作
    <START>: @<start>
    <DATA>: <byte> ... <byte>
     * <byte> 是空格分割的十六进制数据(不带0x前缀).
    <ADDR>: @<start>[,<len>] | @<start>-<end>
     * 定义要被替换的数据段.
    <FILENAME>: <filename>
     * 指定要替换的数据源文件名.
    <ADDR_SRC>: @<start>[,<len>] | @<start>-<end>
     * 定义要用于替换的源文件数据段.
     * <ADDR_SRC>和<ADDR>指定的长度务必兼容.
     * 默认将整个文件用来替换.

 * append <DATA>
 * append <FILENAME> [<ADDR_SRC>]
    在目标文件结尾追加额外数据
    <DATA>: <byte> ... <byte>
    <FILENAME>: <filename>
     * 指定要追加的数据源文件.
    <ADDR_SRC>: @<start>[,<len>] | @<start>-<end>
     * 定义要用于追加的源文件数据段.
     * 默认追加整个文件.

 * delete <ADDR>
    删除目标文件的一部分,尽量原地操作
    <ADDR>: @<start>[,<end>] | @<start>-<end>
     * 指定要删除的目标文件数据段.

 * insert [<START>] <DATA>
 * insert [<START>] <FILENAME> [<ADDR_SRC>]
    向目标文件中插入数据,尽量原地操作
    <START>: @<start>
     * 指定要插入数据的首地址.
     * 默认插入到文件头.
    <DATA>: <byte> ... <byte>
    <FILENAME>: <filename>
     * 指定要插入的数据源文件.
    <ADDR_SRC>: @<start>[,<len>] | @<start>-<end>
     * 定义要用于插入的源文件数据段.
     * 默认插入整个文件.

立即模式
 * calc <expression>
    计算立即表达式
 */

#include <stdio.h>
#include <string.h>

// 判断str是否以pattern开头
int starts_with(const char* str, const char* pattern){
    for(int i=0;pattern[i];i++){
        if(pattern[i]^str[i])
            return 0;
    }
    return 1;
}

// 解析命令行参数
int parser(int argc, char* argv[]){
    for(int i=0;i<argc;i++){
        // strcmp(argv[i],"--");
    }
    return 0;
}

int main(int argc, char* argv[]){
    printf("%d\n",starts_with("asd","ad"));
    return 0;
}