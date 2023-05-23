#include <stdio.h>
#include <string.h>
// reverse関数の定義
void reverse(char *str) {
    // ⽂字列の⻑さを求める
    int len = strlen(str);
    // 後ろから順に⽂字を出⼒する
    for (int i = len - 1; i >= 0; i--) {
        printf("%c", str[i]);
    }
    printf("\n");
}

int main(int argc, char const *argv[]) {
    // reverse関数を呼び出す
    reverse("Hello, World!");
    return 0;
}