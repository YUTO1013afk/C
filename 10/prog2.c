#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE 256

void usage(void);

int main(int argc, char const *argv[]) {
    if (argc < 2) {
        usage();
    }

    for (int i = 1; i < argc; i++) {
        FILE *fp;

        if ((fp = fopen(argv[i], "r")) == NULL) {
            printf("[ERROR] ファイル %s を開けませんでした。\n\n", argv[i]);
            continue;
        }

        printf("== filename:%s ==\n", argv[i]);
        int line_num = 1;
        char line_buf[MAX_LINE];
        while (fgets(line_buf, MAX_LINE, fp) != NULL) {
            printf("%04d: %s", line_num++, line_buf);
        }
        printf("\n");

        fclose(fp);
    }

    return 0;
}

void usage(void) {
    printf("使用方法：プログラム名 ファイル名1 ファイル名2 ...\n");
    exit(1);
}