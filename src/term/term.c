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
#include <stdarg.h>
#include <stdbool.h>
#include "term.h"

#if defined(_WIN32)
# include <windows.h>
# include <conio.h>
#elif defined(__linux__)
# include <sys/ioctl.h>
# include <unistd.h>
# include <termios.h>
#endif

#define MIN(x,y) ((x)<(y)?(x):(y))
#define MAX(x,y) ((x)>(y)?(x):(y))

// 获取终端/控制台大小(以字符计)
// 返回值:返回0为成功,否则失败.
int get_term_size(/*out*/ int* ref_w, /*out*/ int* ref_h){
    if((!ref_w) || (!ref_h))
        return (-1);

#if defined(_WIN32)
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int winw, winh, bufw, bufh;
    if(!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
        return (-1);
    winw=csbi.srWindow.Right-csbi.srWindow.Left+1; // cols
    winh=csbi.srWindow.Bottom-csbi.srWindow.Top+1; // rows
    bufw=csbi.dwSize.X; // cols
    bufh=csbi.dwSize.Y; // rows
    *ref_w=MIN(winw,bufw);
    *ref_h=MIN(winh,bufh);
#elif defined(__linux__)
    struct winsize termsz;
    if(ioctl(0, TIOCGWINSZ , &termsz))
        return (-1);
    *ref_w=termsz.ws_col;
    *ref_h=termsz.ws_row;
#endif

    return 0;
}

// 可设置颜色的printf
void printf_color(int fg, int bg, const char* fmt, ...){
#if defined(_WIN32) && (!defined(_WIN32_USE_VTES) || !_WIN32_USE_VTES)
# define FC_MASK 0x0000000F
# define BC_MASK 0x000000F0

	HANDLE  hStdout;
	WORD    wOldColorAttrs;
    BOOL    bSuccess;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	hStdout=GetStdHandle(STD_OUTPUT_HANDLE);
    if(INVALID_HANDLE_VALUE==hStdout){
        bSuccess=FALSE;
    }else{
        bSuccess=GetConsoleScreenBufferInfo(hStdout, &csbiInfo);
    }
    if(bSuccess){
        wOldColorAttrs = csbiInfo.wAttributes;
        if(FC_DEFAULT==fg)
            fg=wOldColorAttrs&FC_MASK;
        if(BC_DEFAULT==bg)
            bg=wOldColorAttrs&BC_MASK;
        SetConsoleTextAttribute(hStdout, fg|bg);
    }

    va_list args;
    va_start(args,fmt);
    vprintf(fmt,args);
    va_end(args);

    if(bSuccess){
        SetConsoleTextAttribute(hStdout, wOldColorAttrs);
    }
#elif defined(__linux__) || (defined(_WIN32_USE_VTES) && _WIN32_USE_VTES)
# ifdef _WIN32

#   ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#     define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#   endif // ENABLE_VIRTUAL_TERMINAL_PROCESSING

#   ifndef DISABLE_NEWLINE_AUTO_RETURN
#     define DISABLE_NEWLINE_AUTO_RETURN        0x0008
#   endif // DISABLE_NEWLINE_AUTO_RETURN

    int bSuccess=1; // Must init to 1
    HANDLE hStdout;
    hStdout=GetStdHandle(STD_OUTPUT_HANDLE);
    if(INVALID_HANDLE_VALUE==hStdout){
        bSuccess=0;
    }
    DWORD dwOriginalOutMode = 0;
    if(!bSuccess || !GetConsoleMode(hStdout, &dwOriginalOutMode)){
        bSuccess=0;
    }
    DWORD dwOutMode = dwOriginalOutMode|ENABLE_VIRTUAL_TERMINAL_PROCESSING|DISABLE_NEWLINE_AUTO_RETURN;
    if(!bSuccess || !SetConsoleMode(hStdout, dwOutMode)){
        bSuccess=0;
        // we failed to set both modes, try to step down mode gracefully.
        dwOutMode = dwOriginalOutMode|ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        if (!bSuccess || !SetConsoleMode(hStdout, dwOutMode)){
            bSuccess=0;
        }
    }
    if(bSuccess){
# endif

    if(FC_DEFAULT==fg && BC_DEFAULT==bg){
        printf("\033[0m");
    }else if((FC_DEFAULT!=fg && BC_DEFAULT!=bg)){
        printf("\033[%d;%dm",fg,bg);
    }else{ // One in fg/bg is 0
        printf("\033[%dm",fg|bg);
    }

# ifdef _WIN32
    }
# endif

    va_list args;
    va_start(args,fmt);
    vprintf(fmt,args);
    va_end(args);

# ifdef _WIN32
    if(bSuccess){
# endif

    printf("\033[0m");

# ifdef _WIN32
    }
# endif

#endif
}

// 清除终端/控制台内容, and move cursor to upper left corner
// Returned 0 for success, -1 for failure
void clear_term(void){
#if defined(_WIN32) && (!defined(_WIN32_USE_VTES) || !_WIN32_USE_VTES)
    COORD   coordScreen = { 0, 0 };
    BOOL    bSuccess = 1;
    DWORD   cCharsWritten;
    DWORD   dwConSize;
    HANDLE  hConsole;
    CONSOLE_SCREEN_BUFFER_INFO  csbi;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if(!GetConsoleScreenBufferInfo( hConsole, &csbi ))
        return;

    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    if(!FillConsoleOutputCharacter( hConsole, (TCHAR) ' ',
        dwConSize, coordScreen, &cCharsWritten ))
        return;

    if(!GetConsoleScreenBufferInfo( hConsole, &csbi ))
        return;

    if(!FillConsoleOutputAttribute( hConsole, csbi.wAttributes,
        dwConSize, coordScreen, &cCharsWritten ))
        return;

    if(!SetConsoleCursorPosition( hConsole, coordScreen ))
        return;

    return;
#elif defined(__linux__) || (defined(_WIN32_USE_VTES) && _WIN32_USE_VTES)
    printf(" \033[2J\033[H");
    return;
#endif
}

// Suspend the process and wait for user input
// No echo displayed
int get_key(void){
    int ret = K_UNDEF;
#if defined(_WIN32)
    if((ret=getch()) == 0xe0){
        switch(getch()){
        case 72:
            return K_UP;
        case 80:
            return K_DOWN;
        case 75:
            return K_LEFT;
        case 77:
            return K_RIGHT;
        default:
            return K_UNDEF;
        }
    }else{
        return ret;
    }
#elif defined(__linux__)
    char key_buf[1]; // Note that certain key presses are indicated with 3 chars(e.g. arrow keys)
    struct termios tios, tios_pause;

    fflush(stdout);

    tcgetattr(STDIN_FILENO, &tios);

    tios_pause = tios;
    tios_pause.c_lflag&=~ICANON; // 关闭Canonical模式(这样无须换行即可获得输入)
    tios_pause.c_lflag&=~ECHO;   // 关闭回显
    tios_pause.c_cc[VMIN]=1;     // 在非Canonical模式下最少输入1字符即可读取
    tios_pause.c_cc[VTIME]=0;    // read会一直等待输入,无超时

    tcsetattr(STDIN_FILENO, TCSANOW, &tios_pause);

    if(read(STDIN_FILENO,key_buf,1), '\033' == key_buf[0]){
        tios_pause.c_cc[VTIME]=0; // VMIN VTIME均为0, Non blocking
        tios_pause.c_cc[VMIN]=0;  // 用于区分ESC与ESC seq
        tcsetattr(STDIN_FILENO, TCSANOW, &tios_pause);
        if(read(STDIN_FILENO,key_buf,1) == 0){
            ret = '\033';
        }else if('[' == key_buf[0]){
            switch(read(STDIN_FILENO,key_buf,1), key_buf[0]){
                case 'A':
                    ret = K_UP;
                    break;
                case 'B':
                    ret = K_DOWN;
                    break;
                case 'D':
                    ret = K_LEFT;
                    break;
                case 'C':
                    ret = K_RIGHT;
                    break;
                default:
                    ret = K_UNDEF;
            }
        }else{
            ret = K_UNDEF;
        }
    }else{
        ret = key_buf[0];
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &tios);

    return ret;
#endif
}

// * Do NOT delete move_cursor, though temporarily disabled
//
// #if defined(__linux__)
// // 获取终端光标位置(1,1)为原点
// static int locate_cursor(/*out*/ int* ref_x, int* ref_y){
//     if((!ref_y) || (!ref_x))
//         return (-1);
//     printf("\033[6n");
//
//     char key_buf[1];
//     struct termios tios, tios_pause;
//
//     fflush(stdout);
//
//     tcgetattr(STDIN_FILENO, &tios);
//
//     tios_pause = tios;
//     tios_pause.c_lflag&=~ICANON; // 关闭Canonical模式(这样无须换行即可获得输入)
//     tios_pause.c_lflag&=~ECHO;   // 关闭回显
//     tios_pause.c_cc[VMIN]=1;     // 在非Canonical模式下最少输入1字符即可读取
//     tios_pause.c_cc[VTIME]=0;    // read会一直等待输入,无超时
//
//     tcsetattr(STDIN_FILENO, TCSANOW, &tios_pause);
//
//     if(read(STDIN_FILENO,key_buf,1), '\033' != key_buf[0])
//         return (-1);
//     if(read(STDIN_FILENO,key_buf,1), '[' != key_buf[0])
//         return (-1);
//
//     *ref_y=0;
//     for(read(STDIN_FILENO,key_buf,1); key_buf[0]>='0' && key_buf[0]<='9'; read(STDIN_FILENO,key_buf,1)){
//         (*ref_y)=(*ref_y)*10+key_buf[0]-'0';
//     }
//
//     if(';' != key_buf[0])
//         return (-1);
//
//     *ref_x=0;
//     for(read(STDIN_FILENO,key_buf,1); key_buf[0]>='0' && key_buf[0]<='9'; read(STDIN_FILENO,key_buf,1)){
//         (*ref_x)=(*ref_x)*10+key_buf[0]-'0';
//     }
//
//     if('R' != key_buf[0])
//         return (-1);
//
//     return 0;
// }
// #elif (defined(_WIN32_USE_VTES) && _WIN32_USE_VTES)
// static int locate_cursor(/*out*/ int* ref_x, int* ref_y){
//     if((!ref_y) || (!ref_x))
//         return (-1);
//     printf("\033[6n");
//     if(getch() != '\033')
//         return (-1);
//     if(getch() != '[')
//         return (-1);
//
//     int c;
//
//     *ref_y=0;
//     for(c=getch(); c>='0' && c<='9'; c=getch()){
//         (*ref_y)=(*ref_y)*10+c-'0';
//     }
//
//     if(c != ';')
//         return (-1);
//
//     *ref_x=0;
//     for(c=getch(); c>='0' && c<='9'; c=getch()){
//         (*ref_x)=(*ref_x)*10+c-'0';
//     }
//
//     if(c != 'R')
//         return (-1);
//
//     return 0;
// }
// #else // WIN32 w/o VT ESC seq
//     // Use CONSOLE_SCREEN_BUFFER_INFO instead
// #endif
//
// // 移动光标
// // 入参为相对移动量
// int move_cursor(int xrel, int yrel){
//     int w,h;
//     if(get_term_size(&w, &h))
//         return (-1);
// #if defined(_WIN32) && (!defined(_WIN32_USE_VTES) || !_WIN32_USE_VTES)
//     CONSOLE_SCREEN_BUFFER_INFO csbi;
//     GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&csbi);
//     COORD crdDest = {csbi.dwCursorPosition.X+xrel, csbi.dwCursorPosition.Y+yrel};
//     if( crdDest.X<csbi.srWindow.Left || crdDest.X>csbi.srWindow.Right \
//       || crdDest.Y<csbi.srWindow.Top || crdDest.Y>csbi.srWindow.Bottom )
//         return (-1);
//     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),crdDest);
// #elif defined(__linux__) || (defined(_WIN32_USE_VTES) && _WIN32_USE_VTES)
//     int x, y;
//     if(locate_cursor(&x, &y) == (-1))
//         return (-1);
//     x += xrel;
//     y += yrel;
//     if(x<=0 || y<=0 || x>w || y>h)
//         return (-1);
//     printf("\033[%d;%dH", y, x);
// #endif
//     return 0;
// }

// 放置光标
// 入参为绝对位置
int put_cursor(int x, int y){
    int w,h;
    if(get_term_size(&w, &h))
        return (-1);
    if(x<=0 || y<=0 || x>w || y>h)
        return (-1);
#if defined(_WIN32) && (!defined(_WIN32_USE_VTES) || !_WIN32_USE_VTES)
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&csbi);
    COORD crdDest = {csbi.srWindow.Left+x-1,csbi.srWindow.Top+y-1};
    if(SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),crdDest))
        return (-1);
#elif defined(__linux__) || (defined(_WIN32_USE_VTES) && _WIN32_USE_VTES)
    printf("\033[%d;%dH", y, x);
#endif
    return 0;
}
