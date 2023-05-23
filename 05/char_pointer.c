#include <stdio.h>
int main(void) {
char a[5] = {0, 1, 2, 3, 4};
char *p = a; // char *p = &a[0];
printf("変数a[0]のアドレスは%p\n", &a[0]);
printf("変数a[1]のアドレスは%p\n", &a[1]);
printf("変数a[2]のアドレスは%p\n", &a[2]);
printf("変数a[3]のアドレスは%p\n", &a[3]);
printf("変数a[4]のアドレスは%p\n", &a[4]);
printf("変数pは%p\n", p++);
printf("変数pは%p\n", p++);
printf("変数pは%p\n", p++);
printf("変数pは%p\n", p++);
printf("変数pは%p\n", p++);
}