#include <stdio.h>

int main(int argc, char const *argv[]) {
    FILE *file;
    file = fopen("example.txt", "r");
    if (file == NULL) {
        printf("ファイルを開けませんでした。\n");
        return 2;
    }
    // ファイルの操作
    // 　読み込み・書き込み等の処理
    //
    fclose(file); // ファイルを閉じる
    return 0;
}
