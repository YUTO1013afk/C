#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
    FILE *fp;
    if ((fp = fopen("example.txt", "r")) == NULL) {
        printf("ファイルを開けませんでした。\n");
        exit(2);
    }

    char buff[100];
    printf("ファイルexample.txtの最初の2行\n");
    for (int i = 1; i <= 2; i++) {
        if (fgets(buff, 100, fp) != NULL) {
            printf("%02d => %s\n", i, buff);
        } else {
            printf("終端まで読み込みました\n");
        }
    }

    printf("ファイルexample.txtの次の10行\n");
    for (int i = 3; i <= 13; i++) {
        if (fgets(buff, 100, fp) != NULL) {
            printf("%02d => %s\n", i, buff);
        } else {
            printf("%02d : 終端まで読み込みました\n", i);
        }
    }

    fclose(fp); // ファイルを閉じる
    return 0;
}