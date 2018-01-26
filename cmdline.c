/*
 
 # 支持的命令行概览
 
 * h version
 * h help
 * h file ... print ...
 * h file ... replace ...
 * h file ... delete ...
 * h file ... insert ...
 
 # 详细
 
 * version
   > 显示版本信息

 * help
   > 显示命令行帮助

 * file <FILENAME>
   > 指定目标文件名

 * print [<ADDR>] [<FORMAT>] [<ENDIAN>] [<ADDRDISP>] [<COLORDISP>] [<PAGEDDISP>]
   > 指定格式显示目标文件内容
   * <ADDR>: @<start>[,<len>] | @<start>-<end>
     * <start> <len> <end>可以是无符号十进制整数,也可以是0x开头的16进制数据.
     * 默认显示整个文件.
     * 只指定<start>会从该地址显示到文件尾.
   * <FORMAT>: bin1|bin8|bin16|bin32|bin64
               oct8|oct16|oct32|oct64
               hex8|hex16|hex32|hex64
               int8|int16|int32|int64
               uint8|uint16|uint32|uint64
               fix8.d|fix16.d|fix32.d|fix64.d
               ufix8.d|ufix16.d|ufix32.d|ufix64.d
               float|single|double
     * 默认<FORMAT>是"hex8".
     * fix表示定点小数,十进制数"d"用于描述二进制小数点位置.
   * <ENDIAN>: big|little
   * <ADDRDISP>: addr
     * 以表格形式显示数据,并标出地址.
     * 默认不标出数据地址.
   * <COLORDISP>: colorblind|background|foreground
     * 决定相邻数据如何区别显示.
     * "colorblind"表示不以颜色区分,"foreground"表示以前景色区分,"background"表示以背景色区分.
     * 默认的<COLORDISP>是"colorblind".
   * <PAGEDDISP>: paged
     * 决定数据是否分页显示.
     * 默认不分页显示.

 * replace <ADDR> <DATA>
 * replace <ADDR> <FILENAME> [<FILEADDR>]
   > 覆写目标文件的部分数据,尽量原地操作
   * <ADDR>: @<start>[,<len>] | @<start>-<end>
     * 定义要被替换的数据段.
     * 只指定<start>会替换该地址到文件尾的所有数据.
   * <DATA>: <byte> ... <byte>
     * <byte>是空格分割的十六进制数据(不带0x前缀).
   * <FILENAME>: <filename>
     * 指定要替换的数据源文件名.
   * <FILEADDR>: @<start>[,<len>] | @<start>-<end>
     * 定义要用于替换的源文件数据段.
     * 默认将整个文件用来替换.
     * 只指定<start>,则源文件数据段是从该地址到源文件尾的所有数据.

 * delete <ADDR>
   > 删除目标文件的一部分,尽量原地操作
   * <ADDR>: @<start>[,<end>] | @<start>-<end>
     * 指定要删除的目标文件数据段.
     * 只指定<start>会将该地址到文件尾的数据全部删除.

 * insert <LOCATOR> <DATA>
 * insert <LOCATOR> <FILENAME> [<FILEADDR>]
   > 向目标文件中插入数据,尽量原地操作
   * <LOCATOR>: @<start>
     * 指定要插入数据的首地址.
     * "@head"表示插入到文件头,"@tail"表示插入到文件尾.
   * <DATA>: <byte> ... <byte>
   * <FILENAME>: <filename>
     * 指定要插入的数据源文件.
   * <FILEADDR>: @<start>[,<len>] | @<start>-<end>
     * 定义要用于插入的源文件数据段.
     * 默认插入整个文件.
     * 只指定<start>,则源文件数据段是从该地址到源文件尾的所有数据.

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