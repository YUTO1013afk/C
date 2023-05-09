#include <stdio.h>

// 階乗を計算する関数
int factorial(int n) {
  // ベースケース
  if (n == 0) {
    return 1;
  }
  // 再帰ケース
  return n * factorial(n - 1);
}

int main() {
  int x; // ユーザーが⼊⼒する数値
  printf("数値を⼊⼒してください: ");
  scanf("%d", &x); // 数値を読み込む
  printf("%dの階乗は%dです\n", x, factorial(x)); // 階乗を計算して出力する
  return 0;
}