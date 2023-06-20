#include <stdio.h>
int main(int argc, char const *argv[]) {
    char sa[] = "Hello";
    printf("%s %p\n", sa, sa);
    char *sp = "Hello";
    printf("%s %p\n", sp, sp);
    char sb[] = "Hello";
    printf("%s %p\n", sb, sb);
    return 0;
}