#include <stdio.h>
// lower関数の定義
void lower(char *str) {
    // ⽂字列の各要素をループで処理する
    int i = 0;
    while (str[i] != '\0') {
        // ⼤⽂字の場合は⼩⽂字に変換する
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + 32;
        }
        i++;
    }
}

int main(int argc, char const *argv[]) {
    // ⽂字列を定義する
    char str[] = "HELLO, WORLD";
    // lower関数を呼び出す
    lower(str);
    // ⽂字列を出⼒する
    printf("%s\n", str);
    return 0;
}