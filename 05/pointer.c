#include <stdio.h>
int main(int argc, char const *argv[]) {
int a = 10;
int *p = NULL;
printf("aの値:%d\n", a);
p = &a;
printf("pの指し⽰す場所の値:%d\n", *p);
return 0;
}