#include <stdio.h>
void fconcat(char[], char[], char[]);
int main(int argc, char const *argv[]) {
    char str1[] = "Hello, ";
    char str2[] = "World";
    char concat[100]; // 結果を⼊れる配列
    fconcat(concat, str1, str2);
    printf("fconcat : %s\n", concat);
    return 0;
}

void fconcat(char result[], char str1[], char str2[]) {
    // 動作するように書き換える
    char *p = result;       // 結果の配列のポインタ
    while (*str1 != '\0') { // str1の終端に達するまで繰り返す
        *p = *str1;         // str1の文字をresultにコピーする
        p++;                // resultのポインタを次の位置に移動する
        str1++;             // str1のポインタを次の文字に移動する
    }
    while (*str2 != '\0') { // str2の終端に達するまで繰り返す
        *p = *str2;         // str2の文字をresultにコピーする
        p++;                // resultのポインタを次の位置に移動する
        str2++;             // str2のポインタを次の文字に移動する
    }
    *p = '\0'; // resultの終端にヌル文字を入れる
}
