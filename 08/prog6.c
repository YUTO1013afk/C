#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 足し算をする関数
int add(int x, int y) {
    return x + y;
}

// 引き算をする関数
int sub(int x, int y) {
    return x - y;
}

// 掛け算をする関数
int mul(int x, int y) {
    return x * y;
}

// 割り算をする関数
int divide(int x, int y) {
    return x / y;
}

int main(int argc, char **argv) {
    // コマンドライン引数が4つあるかどうかチェックする
    if (argc == 4) {
        // argv[2]とargv[3]を整数に変換する
        int x = atoi(argv[2]);
        int y = atoi(argv[3]);
        // 計算結果を格納する変数resultを宣言する
        int result;
        // argv[1]の値に応じて計算する関数を呼び出す
        if (strcmp(argv[1], "add") == 0) {
            result = add(x, y);
        } else if (strcmp(argv[1], "sub") == 0) {
            result = sub(x, y);
        } else if (strcmp(argv[1], "mul") == 0) {
            result = mul(x, y);
        } else if (strcmp(argv[1], "div") == 0) {
            result = divide(x, y);
        } else {
            // 不正なコマンド名の場合はエラーメッセージを出力して終了する
            printf("正しいコマンド名を入力してください\n");
            return 1;
        }
        // 計算式と計算結果を出力する
        printf("%d", x);
        if (strcmp(argv[1], "add") == 0) {
            printf("+");
        } else if (strcmp(argv[1], "sub") == 0) {
            printf("-");
        } else if (strcmp(argv[1], "mul") == 0) {
            printf("*");
        } else if (strcmp(argv[1], "div") == 0) {
            printf("/");
        }
        printf("%d=", y);
        printf("%d\n", result);
    } else {
        // コマンドライン引数が4つでない場合はエラーメッセージを出力する
        printf("引数の数が正しくありません\n");
    }
    return 0;
}
