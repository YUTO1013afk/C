#include <stdio.h>

int main(void) {
  // 配列の要素数をユーザーから入力する
  int n;
  printf("配列の要素数を入力してください: ");
  scanf("%d", &n);

  // 配列を宣言する
  int array[n];

  // 配列の要素に整数を入力する
  for (int i = 0; i < n; i++) {
    printf("array[%d]に入力する整数を入力してください: ", i);
    scanf("%d", &array[i]);
  }

  // 配列の最大値と最小値を求める
  int max = array[0]; // 最大値を初期化する
  int min = array[0]; // 最小値を初期化する
  for (int i = 1; i < n; i++) {
    if (array[i] > max) { // より大きい値があれば最大値を更新する
      max = array[i];
    }
    if (array[i] < min) { // より小さい値があれば最小値を更新する
      min = array[i];
    }
  }

  // 最大値と最小値を表示する
  printf("配列の最大値は%dです。\n", max);
  printf("配列の最小値は%dです。\n", min);

  return 0;
}