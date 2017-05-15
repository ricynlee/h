#include <stdio.h>
#include "term.h"

int main(){
    int w,h;
    get_term_size(&w,&h);
    printf_color(FC_RED,BC_CYAN,  "width:%d",w);
    printf_color(FC_DEFAULT,BC_DEFAULT," ");
    printf_color(FC_RED,BC_SILVER,"height:%d\n",h);
    
    pause();
    
    return 0;
}
