#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
    FILE *fp;
    if ((fp = fopen("example.txt", "r")) == NULL) {
        printf("ファイルを開けませんでした。\n");
        exit(2);
    }
    // ファイルの操作
    // 　読み込み・書き込み等の処理
    //
    fclose(fp); // ファイルを閉じる
    return 0;
}