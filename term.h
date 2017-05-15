#ifndef _H_TERM_H
#define _H_TERM_H

//
// Type & constant definitions
//
#define _WIN32_USE_VTES 1 /*Win10/ConEmu或可在Win32上支持VTES*/

#if defined(_WIN32) && !_WIN32_USE_VTES
# include <windows.h>
  typedef enum {
      FC_BLACK       = 0,
      FC_DARKRED     = FOREGROUND_RED,
      FC_DARKGREEN   = FOREGROUND_GREEN,
      FC_DARKYELLOW  = FOREGROUND_RED|FOREGROUND_GREEN,
      FC_DARKBLUE    = FOREGROUND_BLUE,
      FC_DARKMAGENTA = FOREGROUND_RED|FOREGROUND_BLUE,
      FC_DARKCYAN    = FOREGROUND_GREEN|FOREGROUND_BLUE,
      FC_SILVER      = FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE,
      FC_GRAY        = FOREGROUND_INTENSITY,
      FC_RED         = FOREGROUND_INTENSITY|FOREGROUND_RED,
      FC_GREEN       = FOREGROUND_INTENSITY|FOREGROUND_GREEN,
      FC_YELLOW      = FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN,
      FC_BLUE        = FOREGROUND_INTENSITY|FOREGROUND_BLUE,
      FC_MAGENTA     = FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_BLUE,
      FC_CYAN        = FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE,
      FC_WHITE       = FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE,
      FC_DEFAULT     = (-1)
  } FC;

# define FC_MASK 0x0000000F

  typedef enum {
      BC_BLACK       = 0,
      BC_DARKRED     = BACKGROUND_RED,
      BC_DARKGREEN   = BACKGROUND_GREEN,
      BC_DARKYELLOW  = BACKGROUND_RED|BACKGROUND_GREEN,
      BC_DARKBLUE    = BACKGROUND_BLUE,
      BC_DARKMAGENTA = BACKGROUND_RED|BACKGROUND_BLUE,
      BC_DARKCYAN    = BACKGROUND_GREEN|BACKGROUND_BLUE,
      BC_SILVER      = BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE,
      BC_GRAY        = BACKGROUND_INTENSITY,
      BC_RED         = BACKGROUND_INTENSITY|BACKGROUND_RED,
      BC_GREEN       = BACKGROUND_INTENSITY|BACKGROUND_GREEN,
      BC_YELLOW      = BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN,
      BC_BLUE        = BACKGROUND_INTENSITY|BACKGROUND_BLUE,
      BC_MAGENTA     = BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_BLUE,
      BC_CYAN        = BACKGROUND_INTENSITY|BACKGROUND_GREEN|BACKGROUND_BLUE,
      BC_WHITE       = BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE,
      BC_DEFAULT     = (-1)
  } BC;

# define BC_MASK 0x000000F0
#elif defined(__linux__) || _WIN32_USE_VTES
  // Virtual Terminal Escape Sequence (VTES for short)
  typedef enum {
      FC_BLACK       = 30,
      FC_DARKRED     = 31,
      FC_DARKGREEN   = 32,
      FC_DARKYELLOW  = 33,
      FC_DARKBLUE    = 34,
      FC_DARKMAGENTA = 35,
      FC_DARKCYAN    = 36,
      FC_SILVER      = 37,
      FC_GRAY        = 90,
      FC_RED         = 91,
      FC_GREEN       = 92,
      FC_YELLOW      = 93,
      FC_BLUE        = 94,
      FC_MAGENTA     = 95,
      FC_CYAN        = 96,
      FC_WHITE       = 97,
      FC_DEFAULT     = 0
  } FC;

  typedef enum {
      BC_BLACK       = 40 ,
      BC_DARKRED     = 41 ,
      BC_DARKGREEN   = 42 ,
      BC_DARKYELLOW  = 43 ,
      BC_DARKBLUE    = 44 ,
      BC_DARKMAGENTA = 45 ,
      BC_DARKCYAN    = 46 ,
      BC_SILVER      = 47 ,
      BC_GRAY        = 100,
      BC_RED         = 101,
      BC_GREEN       = 102,
      BC_YELLOW      = 103,
      BC_BLUE        = 104,
      BC_MAGENTA     = 105,
      BC_CYAN        = 106,
      BC_WHITE       = 107,
      BC_DEFAULT     = 0
  } BC;
#endif

//
// Functions declarations
//
extern int  get_term_size(/*out*/ int* ref_w, /*out*/ int* ref_h);
extern void printf_color(/*in*/ FC fc, /*in*/ BC bc, /*in*/ const char* fmt, /*in*/...);
extern int  pause(void);

#endif  // _H_TERM_H
