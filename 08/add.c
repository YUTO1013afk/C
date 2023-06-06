#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    // コマンドライン引数が2つ以上あるかどうかチェックする
    if (argc >= 2) {
        // 足し算の結果を格納する変数sumを初期化する
        int sum = 0;
        // for文でargv[1]からargv[argc-1]まで順番にアクセスし、atoi関数で整数に変換してsumに加算する
        for (int i = 1; i < argc; i++) {
            sum += atoi(argv[i]);
        }
        // sumの値と渡された引数を出力する
        for (int i = 1; i < argc - 1; i++) {
            printf("%s + ", argv[i]);
        }
        printf("%s = ", argv[argc - 1]);
        printf("%d\n", sum);
    } else {
        // エラーメッセージを出力する
        printf("Please specify at least one number.\n");
    }
    return 0;
}
