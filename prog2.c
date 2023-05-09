#include <stdio.h>

int main () {
  int i; // ループ用の変数
  int number; // ⼊⼒された数値
  int flag = 0; // 素数かどうかを判定するフラグ

  printf("自然数 = "); // ⼊⼒を促すメッセージ
  scanf("%d", &number); // ⼊⼒された数値をnumberに代⼊

  for( i=2;i<number;++i ) { // 2からnumberより1小さい数までループ
    if( number%i==0 ) { // numberをiで割った余りが0なら
      flag = 1; // flagを1にする
      break; // ループを抜ける
    }
  }

  if( flag==0 ) // flagが0なら
    printf("%d は素数です。 \n",number); // 素数であると出⼒
  else // flagが0でなければ
    printf("%d は素数ではありません。 \n",number); // 素数でないと出⼒

  return 0;
}