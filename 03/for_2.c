#include <stdio.h>
int main(int argc, char const *argv[]) {
int i = 0;
for (;;) {
// if (i++ >= 5) {
// break;
// }
printf("%d回⽬のループです\n", ++i);  // ← 変更
}
printf("for⽂の後に実⾏されます\n");
return 0;
}