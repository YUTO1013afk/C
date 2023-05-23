#include <stdio.h>
void print(char[]);
int main(int argc, char const *argv[]) {
char hello[] = "Hello World";
print(hello); // 配列名のみ記述する[]は書かない
return 0;
}
void print(char str[]) {
printf("%s\n", str);
}