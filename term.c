#include <stdio.h>
#include <stdarg.h>
#include "term.h"

#if defined(_WIN32)
  #include <windows.h>
  #include <conio.h>
#elif defined(__linux__)
  #include <sys/ioctl.h>
  #include <unistd.h>
  #include <termios.h>
#endif

#define MIN(x,y) ((x)<(y)?(x):(y))
#define MAX(x,y) ((x)>(y)?(x):(y))

// ��ȡ�ն�/����̨��С(���ַ���)
// bool get_term_size(/*out*/ int* ref_w, /*out*/ int* ref_h);
// ����ֵ:����trueΪ�ɹ�,����ʧ��.
bool get_term_size(/*out*/ int* ref_w, /*out*/ int* ref_h){
    if((!ref_w) || (!ref_h))
        return false;

  #if defined(_WIN32)
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int winw, winh, bufw, bufh;
    if(!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
        return false;
    winw=csbi.srWindow.Right-csbi.srWindow.Left+1; // cols
    winh=csbi.srWindow.Bottom-csbi.srWindow.Top+1; // rows
    bufw=csbi.dwSize.X; // cols
    bufh=csbi.dwSize.Y; // rows
    *ref_w=MIN(winw,bufw);
    *ref_h=MIN(winh,bufh);
  #elif defined(__linux__)
    struct winsize termsz;
    if(ioctl(0, TIOCGWINSZ , &termsz))
        return false;
    *ref_w=termsz.ws_col;
    *ref_h=termsz.ws_row;
  #endif

    return true;
}

// ��������ɫ��printf
// void printf_color(FOREGROND_COLOR fc, BACKGROUND_COLOR bc, ...);
//
void printf_color(/*in*/ FC fc, /*in*/ BC bc, /*in*/ const char* fmt, /*in*/...){
  #if defined(_WIN32) && !_WIN32_USE_VTES
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
        if(FC_DEFAULT==fc)
            fc=wOldColorAttrs&FC_MASK;
        if(BC_DEFAULT==bc)
            bc=wOldColorAttrs&BC_MASK;
        SetConsoleTextAttribute(hStdout, fc|bc);
    }

    va_list args;
    va_start(args,fmt);
    vprintf(fmt,args);
    va_end(args);

    if(bSuccess){
        SetConsoleTextAttribute(hStdout, wOldColorAttrs);
    }
  #elif defined(__linux__) || _WIN32_USE_VTES
    #ifdef _WIN32
    
    #ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
    #define ENABLE_VIRTUAL_TERMINAL_PROCESSING  0x0004
    #endif // ENABLE_VIRTUAL_TERMINAL_PROCESSING
    
    #ifndef DISABLE_NEWLINE_AUTO_RETURN
    #define DISABLE_NEWLINE_AUTO_RETURN         0x0008
    #endif // DISABLE_NEWLINE_AUTO_RETURN

    bool bSuccess=true; // Must init to true
	HANDLE hStdout;
	hStdout=GetStdHandle(STD_OUTPUT_HANDLE);
    if(INVALID_HANDLE_VALUE==hStdout){
        bSuccess=false;
    }
    DWORD dwOriginalOutMode = 0;
    if(!bSuccess || !GetConsoleMode(hStdout, &dwOriginalOutMode)){
        bSuccess=false;
    }
    DWORD dwOutMode = dwOriginalOutMode|ENABLE_VIRTUAL_TERMINAL_PROCESSING|DISABLE_NEWLINE_AUTO_RETURN;
    if(!bSuccess || !SetConsoleMode(hStdout, dwOutMode)){
        bSuccess=false;
        // we failed to set both modes, try to step down mode gracefully.
        dwOutMode = dwOriginalOutMode|ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        if (!bSuccess || !SetConsoleMode(hStdout, dwOutMode)){
            bSuccess=false;
        }
    }
    if(bSuccess){
    #endif

    if(FC_DEFAULT==fc && BC_DEFAULT==bc){
        printf("\x1b[0m");
    }else if((FC_DEFAULT!=fc && BC_DEFAULT!=bc)){
        printf("\x1b[%d;%dm",fc,bc);
    }else{ // One in fc/bc is 0
        printf("\x1b[%dm",fc|bc);
    }

    #ifdef _WIN32
    }
    #endif

    va_list args;
    va_start(args,fmt);
    vprintf(fmt,args);
    va_end(args);

    #ifdef _WIN32
    if(bSuccess){
    #endif

    printf("\x1b[0m");

    #ifdef _WIN32
    }
    #endif

  #endif
}

// �������,�ȴ��û�����
// int pause(void);
// ����ֵ:������ASCII��
int pause(void){
  #if defined(_WIN32)
    return getch();
  #elif defined(__linux__)
    char inbuf;
    struct termios tios;
    bool bSuccess=true; // Must init to true
    fflush(stdout);
    
    if(tcgetattr(STDIN_FILENO, &tios)<0)
        bSuccess=false;
    
    tios.c_lflag&=~ICANON; // �ر�Canonicalģʽ(�������뻻�м��ɻ������)
    tios.c_lflag&=~ECHO;   // �رջ���
    tios.c_cc[VMIN]=1;     // �ڷ�Canonicalģʽ����������1�ַ����ɶ�ȡ
    tios.c_cc[VTIME]=0;    // read��һֱ�ȴ�����,�޳�ʱ
    if(tcsetattr(STDIN_FILENO, TCSANOW, &tios)<0) // �޸Ĳ�������Ч
        bSuccess=false;
    
    if(read(STDIN_FILENO,&inbuf,1 /*bytes to read*/)<0)
        bSuccess=false;
    
    tios.c_lflag|=ICANON;
    tios.c_lflag|=ECHO;
    if(tcsetattr(STDIN_FILENO, TCSANOW, &tios)<0)
        bSuccess=false;

    return (bSuccess ? (int)inbuf : 0);
  #endif
}
