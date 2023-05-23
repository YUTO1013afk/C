#include <stdio.h>
int main(void) {
char str[100];
printf("変数strのアドレスは%p\n", str);
printf("変数str[0]のアドレスは%p\n", &str[0]);
}