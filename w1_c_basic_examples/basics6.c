// ===========================
// compile on the command line with
// gcc basics6.c -o basics6
// ===========================
#include <stdio.h>

int main(){

    int a = 5;
    char b = 'b';
    char c = 'c';

    printf("a address = %p\n",(int*)&a);
    printf("b address = %p\n",(char*)&b);
    printf("c address = %p\n",(char*)&c);

    return 0;
}
