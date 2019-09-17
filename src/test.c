/*
Copyright (c) 2017 ricynlee

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */

#include <stdio.h>
#include <string.h>
#include "term/term.h"

#define HELP_MSG_MAX_LINES 128
static char* HELP_MSG[] = {
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
    "  > Display the file\'s content using specified format. Sub-options\' order may change.",
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
    "              float|float32|single|double|float64",
    "    * Default <FORMAT> is,\"hex8\".",
    "    * \"fix\" stands for fixed-point decimals, and dec number \"d\" sets the decimal point.",
    "  * <ENDIAN>: big|little",
    "  * <ADDRDISP>: addr",
    "    * Addr is displayed along with data (in the form of a table).",
    "    * By default, no addr is displayed.",
    "  * <COLORDISP>: colorblind|background|foreground",
    "    * Specifies how neighboring data is distinguished.",
    "    * \"colorblind\" stands for no distinguishment using color, and try \"foreground\" and \"background\".",
    "    * By default <COLORDISP> is \"colorblind\".",
    "  * <PAGEDDISP>: paged",
    "    * Specifiy if data is displayed page by page.",
    "    * Not paged by default.",
    "",
    "* replace <ADDR> with <DATA>",
    "* replace <ADDR> with <FILENAME> [<FILEADDR>]",
    "  > Rewrite part of target file. In-place if possible. Sub-options\' order is fixed.",
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
    "* insert <DATA> to <LOCATOR>",
    "* insert <FILENAME> [<FILEADDR>] to <LOCATOR>",
    "  > Add data to the target file. In-place if possible. Sub-options\' order is fixed.",
    "  * <DATA>: <byte> ... <byte>",
    "  * <LOCATOR>: @<start>",
    "    * Specify the initial address of inserted data in the target file.",
    "    * \"@head\" stands for offset 0, \"@tail\" for EOF.",
    "  * <FILENAME>: <filename>",
    "    * Specify a source file to be inserted to the target file.",
    "  * <FILEADDR>: @<start>[,<len>] | @<start>-<end>",
    "    * Specify the data segment in the in the source file to be inserted.",
    "    * By default the whole source file is inserted.",
    "    * With only <start> specified, all data in the source file after this offset will be inserted."
};

#define MIN(x,y) ((x)<(y)?(x):(y))
#define MAX(x,y) ((x)>(y)?(x):(y))
// 显示帮助信息(Horizontal & vertical scrollable with arrow keys)
void prn_help_msg(void){
    int max_x = 0, max_y = sizeof(HELP_MSG)/sizeof(char*)-1; // Size of HELP_MSG
    for(int i=0; i<=max_y; i++){
        max_x = MAX((signed)(strlen(HELP_MSG[i])-1), max_x);
    }

    int tsz_x, tsz_y; // Size of current terminal/console
    int pos_x = 0, pos_y = 0; // Display origin of HELP_MSG
    int prev_tsz_x, prev_tsz_y, prev_pos_x, prev_pos_y=-1;

    while(1){ // Checking if arrow key pressed
        get_term_size(&tsz_x, &tsz_y);

        if(pos_x!=prev_pos_x || pos_y!=prev_pos_y || tsz_x!=prev_tsz_x || tsz_y!=prev_tsz_y){
            clear_term();

            for(int i=pos_y; i<=MIN(max_y, pos_y+tsz_y-2); i++){
#if defined(__WIN32)
                printf("%-.*s\n", tsz_x-1, HELP_MSG[i] + MIN(strlen(HELP_MSG[i]), pos_x));
#elif defined(__linux__)
                printf("%-.*s\n", tsz_x, HELP_MSG[i] + MIN(strlen(HELP_MSG[i]), pos_x));
#endif
            }

            prev_pos_x = pos_x;
            prev_pos_y = pos_y;
            prev_tsz_x = tsz_x;
            prev_tsz_y = tsz_y;

            printf_color(FC_DEFAULT, BC_DARKGREEN, "PRESS ARROW KEYS TO SCROLL");
        }


        switch( get_key() ){
            case K_UP:
                if(pos_y>0)
                    pos_y--;
                break;
            case K_DOWN:
                if(pos_y<max_y-tsz_y+2)
                    pos_y++;
                break;
            case K_LEFT:
                if(pos_x>0)
                    pos_x--;
                break;
            case K_RIGHT:
                if(pos_x<max_x-tsz_x+2)
                    pos_x++;
                break;
            default:
                printf("\n");
                return;
        }
    }
}

int main(){
    prn_help_msg();
    return 0;
}