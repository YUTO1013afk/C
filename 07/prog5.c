#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    // コマンドライン引数が2つ以上あるかどうかチェックする
    if (argc >= 2) {
        // for文でargv[argc-1]からargv[1]まで逆順にアクセスし、printf関数で各文字列とスペースを出力する
        for (int i = argc - 1; i >= 1; i--) {
            printf("%s ", argv[i]);
        }
        // 改行を出力する
        printf("\n");
    } else {
        // エラーメッセージを出力する
        printf("引数の数が正しくありません\n");
    }
    return 0;
}
