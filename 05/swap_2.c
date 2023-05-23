#include <stdio.h>
void swap(int, int);
int main(int argc, char const *argv[]) {
int a = 10, b = 20;
printf("a:%d , b:%d\n", a, b);
// ⼊れ替え処理
swap(a, b);
printf("a:%d , b:%d\n", a, b);
return 0;
}

void swap(int x, int y) {
int temp;
printf(" x:%d , y:%d\n", x, y);
temp = x;
x = y;
y = temp;
printf(" x:%d , y:%d\n", x, y);
}