#include <stdio.h>
// lower関数の定義
char lower(char c) {
  // ⼤⽂字の場合は⼩⽂字に変換する
  if (c >= 'A' && c <= 'Z') {
    c = c + 32;
  }
  // ⽂字を返す
  return c;
}

int main(int argc, char const *argv[]) {
  // ⽂字列の配列を定義する
  char *strs[] = {"HELLO, WORLD"};
  // 配列の要素数を求める
  int n = sizeof(strs) / sizeof(strs[0]);
  // 配列の各要素をループで処理する
  for (int i = 0; i < n; i++) {
    // ⽂字列の⻑さを求める
    int len = strlen(strs[i]);
    // ⽂字列の各⽂字をループで処理する
    for (int j = 0; j < len; j++) {
      // lower関数を呼び出して出⼒する
      printf("%c", lower(strs[i][j]));
    }
    printf("\n");
  }
  return 0;
}