/*
 * --version
    Display version information
    
 * --help
    Display help content

File mode
 * --file <FILENAME>
    Specify target file
    
 * --print [<ADDR>] [<FORMAT>] [<ENDIAN>] [<BITWIDTH>] [<LABELDISP>] [<COLORDISP>] [<PAGEDDISP>]
    Display file content
    <ADDR>: @<start,len>|@<start-end>
     * By default whole file is displayed.
    <FORMAT>: bin|oct|hex|dec[,signed]|dec,unsigned|fixed[,signed]|fixed,unsigned|float
     * By default <FORMAT> is "hex".
    <ENDIAN>: big|little
    <BITWIDTH>: <bitwidth>[.<decimalplace>]
     * <bitwidth> can be 1,8,16,32,64, where 1 is only applicable when <FORMAT> is "bin". When <FORMAT> is "float", only 32 or 64 is applicable. By default <bitwidth> is 8.
     * <decimalplace> is only applicable when <FORMAT> contains "fixed". Display values of data are dec*2^<decimalplace>. By default <decimalplace> is 0.
    <ADDRDISP>: label:on|addr:off
     * By default <ADDRDISP> is "on".
    <COLORDISP>: color:blind|color:background|color:foreground
     * Decides how neighbouring data are distinguished. By default <COLORDISP> is "colorblind".
    <PAGEDDISP>: paged:on|off
     * Decides whether file is displayed page by page. On by default.
    
 * --replace <ADDR> <DATA>|<FILE>
    Overwrite (part of) file with data (of the same length)
    <ADDR>: @<start>,<len>|@<start>-<end>
     * <start> shoud be a decimal or hexidecimal(begin with 0x) number.
    <DATA>: <byte> ... <byte>
     * Bytes in hex form, separated by spaces.
    <FILE>: <file> @<start>

 * --append <DATA>|<FILE>
    Append extra data to the end of file
    <DATA>: <byte> ... <byte>
     * Bytes in hex form, separated by spaces.
    <FILE>: <file> @<start>,<len>|@<start>-<end>

 * --delete
    Delete (part of) file
     * Not gonna be implemented recently.
    
 * --insert
    Insert data into (middle of) file
     * Not gonna be implemented recently.

Calculator mode
 * --calc <expression>
    Calculate the expression
 */

#include<stdio.h> 

int parser(int argc, char* argv[]){
    for(int i=0;i<argc;i++)
        printf("%s\n",argv[i]);
    return 0;
}

int main(int argc, char* argv[]){
    return parser(argc,argv);
}