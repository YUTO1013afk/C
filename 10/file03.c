#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
    FILE *fp;
    if ((fp = fopen("example.txt", "r")) == NULL) {
        printf("ファイルを開けませんでした。\n");
        exit(2);
    }

    char ch;
    printf("ファイルexample.txtの最初の10文字\n");
    for (int i = 1; i <= 10; i++) {
        ch = fgetc(fp);
        printf("%02d => (%02x) %c\n", i, ch, ch);
    }

    printf("ファイルexample.txtの次の10文字\n");
    for (int i = 11; i <= 20; i++) {
        ch = fgetc(fp);
        printf("%02d => (%02x) %c\n", i, ch, ch);
    }

    fclose(fp); // ファイルを閉じる
    return 0;
}