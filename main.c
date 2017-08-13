#include <stdio.h>
#include "term/term.h"
#include "file/file.h"
#include <errno.h>

int main(){
    off_t n_byte=0x140000000;
    truncate("a.txt", n_byte);
    return errno;
}
