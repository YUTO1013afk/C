#include <stdbool.h>
#include <stdio.h>
int main(int argc, char const *argv[]) {
char str1[] = "ABCDE";
char str2[] = "ABCDEF";
int match = true; // bool

// ⽐較する処理を書いてみよう
// ⽂字列の最後にNULL文字があることを利⽤してループを回す
int i = 0;
while (str1[i] != '\0' && str2[i] != '\0') {
  // ⽂字列の要素が異なる場合は⼀致しない
  if (str1[i] != str2[i]) {
    match = false;
    break;
  }
  i++;
}
// ループを抜けた後に⽂字列の最後に到達していない場合は⼀致しない
if (str1[i] != '\0' || str2[i] != '\0') {
  match = false;
}

if (match) {
printf("⽂字列は⼀致しています\n");
} else {
printf("⽂字列は⼀致していません\n");
}
return 0;
}