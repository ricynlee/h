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

#ifndef _H_TERM_H
#define _H_TERM_H

//
// Type & constant definitions
//
#if defined(_WIN32) && (!defined(_WIN32_USE_VTES) || !_WIN32_USE_VTES)
# include <windows.h>

  #define FC_BLACK       (0)
  #define FC_DARKRED     (FOREGROUND_RED)
  #define FC_DARKGREEN   (FOREGROUND_GREEN)
  #define FC_DARKYELLOW  (FOREGROUND_RED|FOREGROUND_GREEN)
  #define FC_DARKBLUE    (FOREGROUND_BLUE)
  #define FC_DARKMAGENTA (FOREGROUND_RED|FOREGROUND_BLUE)
  #define FC_DARKCYAN    (FOREGROUND_GREEN|FOREGROUND_BLUE)
  #define FC_SILVER      (FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE)
  #define FC_GRAY        (FOREGROUND_INTENSITY)
  #define FC_RED         (FOREGROUND_INTENSITY|FOREGROUND_RED)
  #define FC_GREEN       (FOREGROUND_INTENSITY|FOREGROUND_GREEN)
  #define FC_YELLOW      (FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN)
  #define FC_BLUE        (FOREGROUND_INTENSITY|FOREGROUND_BLUE)
  #define FC_MAGENTA     (FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_BLUE)
  #define FC_CYAN        (FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE)
  #define FC_WHITE       (FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE)
  #define FC_DEFAULT     (-1)

  #define BC_BLACK       (0)
  #define BC_DARKRED     (BACKGROUND_RED)
  #define BC_DARKGREEN   (BACKGROUND_GREEN)
  #define BC_DARKYELLOW  (BACKGROUND_RED|BACKGROUND_GREEN)
  #define BC_DARKBLUE    (BACKGROUND_BLUE)
  #define BC_DARKMAGENTA (BACKGROUND_RED|BACKGROUND_BLUE)
  #define BC_DARKCYAN    (BACKGROUND_GREEN|BACKGROUND_BLUE)
  #define BC_SILVER      (BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE)
  #define BC_GRAY        (BACKGROUND_INTENSITY)
  #define BC_RED         (BACKGROUND_INTENSITY|BACKGROUND_RED)
  #define BC_GREEN       (BACKGROUND_INTENSITY|BACKGROUND_GREEN)
  #define BC_YELLOW      (BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN)
  #define BC_BLUE        (BACKGROUND_INTENSITY|BACKGROUND_BLUE)
  #define BC_MAGENTA     (BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_BLUE)
  #define BC_CYAN        (BACKGROUND_INTENSITY|BACKGROUND_GREEN|BACKGROUND_BLUE)
  #define BC_WHITE       (BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE)
  #define BC_DEFAULT     (-1)

#elif defined(__linux__) || (defined(_WIN32_USE_VTES) && _WIN32_USE_VTES)
  // Virtual Terminal Escape Sequence (VTES for short)
  typedef enum {
      FC_BLACK       = 30
      FC_DARKRED     = 31
      FC_DARKGREEN   = 32
      FC_DARKYELLOW  = 33
      FC_DARKBLUE    = 34
      FC_DARKMAGENTA = 35
      FC_DARKCYAN    = 36
      FC_SILVER      = 37
      FC_GRAY        = 90
      FC_RED         = 91
      FC_GREEN       = 92
      FC_YELLOW      = 93
      FC_BLUE        = 94
      FC_MAGENTA     = 95
      FC_CYAN        = 96
      FC_WHITE       = 97
      FC_DEFAULT     = 0
  } FC;

  typedef enum {
      BC_BLACK       = 40
      BC_DARKRED     = 41
      BC_DARKGREEN   = 42
      BC_DARKYELLOW  = 43
      BC_DARKBLUE    = 44
      BC_DARKMAGENTA = 45
      BC_DARKCYAN    = 46
      BC_SILVER      = 47
      BC_GRAY        = 100
      BC_RED         = 101
      BC_GREEN       = 102
      BC_YELLOW      = 103
      BC_BLUE        = 104
      BC_MAGENTA     = 105
      BC_CYAN        = 106
      BC_WHITE       = 107
      BC_DEFAULT     = 0
  } BC;
#endif

typedef enum{
    K_UNDEF = -1,

    // Special keys
    K_UP    = 256, // <=255 reserved for ASCII
    K_DOWN  ,
    K_LEFT  ,
    K_RIGHT ,

    K_BUTT
}KEY_PRESS;


//
// Functions declarations
//
extern int  get_term_size(/*out*/ int* ref_w, /*out*/ int* ref_h);
extern void printf_color(/*in*/ int fg, /*in*/ int bg, /*in*/ const char* fmt, /*in*/...);
extern void clear_term(void);
extern int  get_key(void);
extern int  put_cursor(int x, int y);

#endif  // _H_TERM_H
