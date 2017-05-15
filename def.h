#ifndef _H_DEF_H
#define _H_DEF_H

//
// Type definitions
// 
#define _C99_VERNO  199901L
#if defined(__STDC_VERSION__)&&(__STDC_VERSION__>=_C99_VERNO)
  // C99+
  #include <stdint.h>
  typedef _Bool bool;
#else
  // C std ver too low
  #error("C99 or above C standard required")
#endif

//
// Constant definitions
//
#define true    1
#define false   0

#endif // _H_DEF_H