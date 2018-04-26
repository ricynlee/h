#include <stdio.h>
#include "term/term.h"
#include "file/file.h"
#include <errno.h>

int main(){
    int ch;
    while(ch = getch()){
        printf("Input %d\n",ch);
    }
}
