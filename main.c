#include <stdio.h>
#include "term.h"
#include "file.h"

int main(){
    int n_byte;
    printf("输入期望的字节数:");
    scanf("%d",&n_byte);
    truncate("a.txt", n_byte);
    return 0;
}
