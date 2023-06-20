#include <stdio.h>
int main(int argc, char const *argv[]) {
    char sa[] = "Hello";
    printf("%s\n", sa);
    sa[1] = 'E';
    printf("%s\n", sa);
    char *sp = "Hello";
    printf("%s\n", sp);
    *(sp + 1) = 'E'; // この操作はできない
    // sp[1] = 'E';
    printf("%s\n", sp);
}