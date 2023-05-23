#include <stdio.h>
void lower(char *str);
int main() {
    char str[] = "HELLO, World!";
    printf("before:%s\n", str);
    lower(str);
    printf("after :%s\n", str);
    return 0;
}

void lower(char *str) {
    // 各自コードを作成
    while (*str != '\0') {                // 文字列の終端に達するまで繰り返す
        if (*str >= 'A' && *str <= 'Z') { // 大文字なら
            *str = *str + 32;             // 小文字に変換する
        }
        str++; // ポインタを次の文字に移動する
    }
}
