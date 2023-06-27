#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE 256

int main(int argc, char const *argv[]) {
    FILE *fp;
    if ((fp = fopen("prog1.c", "r")) == NULL) {
        printf("ファイルを開けませんでした。\n");
        exit(2);
    }

    int line_num = 1;

    char line_buf[MAX_LINE];
    while (fgets(line_buf, MAX_LINE, fp) != NULL) {
        // 行番号の表示
        printf("%04d:", line_num++);
        // 読み込んだファイルの１行を表示
        printf("%s", line_buf);
    }
    printf("\n"); // 念の為、最後に改行を出力

    fclose(fp); // ファイルを閉じる
    return 0;
}
