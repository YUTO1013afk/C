#include <stdio.h>
#include <string.h>
int main(int argc, char const *argv[]) {
    char *sp, sa[100];
    strcpy(sa, "Hello");
    printf("%s\n", sa);
    strcpy(sp, "Hello"); // この操作はできない
    printf("%s\n", sa);
    return 0;
}