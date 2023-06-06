#include <stdio.h>
#include <string.h>

// 文字列を逆順に出力する関数
void reverse(char *str) {
    // 文字列の長さを取得する
    int len = strlen(str);
    // for文で文字列の最後から先頭まで順番にアクセスし、printf関数で各文字を出力する
    for (int i = len - 1; i >= 0; i--) {
        printf("%c", str[i]);
    }
    // スペースを出力する
    printf(" ");
}

int main(int argc, char **argv) {
    // コマンドライン引数が2つ以上あるかどうかチェックする
    if (argc >= 2) {
        // for文でargv[1]からargv[argc-1]まで順番にアクセスし、各文字列を逆順に出力する関数reverseを呼び出す
        for (int i = 1; i < argc; i++) {
            reverse(argv[i]);
        }
        // 改行を出力する
        printf("\n");
    } else {
        // エラーメッセージを出力する
        printf("引数の数が正しくありません\n");
    }
    return 0;
}
