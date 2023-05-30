#include <stdio.h>

void func_a(void) {
    printf("Called func_a()\n");
}

void func_b(void) {
    printf("Called func_b()\n");
}

int main(void) {
    char input;                             // 入力された⽂字を格納する変数
    printf("Enter a or b: ");               // ⽂字の入力を促す
    scanf("%c", &input);                    // ⽂字を読み込む
    switch (input) {                        // ⽂字によって分岐する
    case 'a':                               // aの場合
        func_a();                           // func_a関数を呼び出す
        break;                              // switch文から抜ける
    case 'b':                               // bの場合
        func_b();                           // func_b関数を呼び出す
        break;                              // switch文から抜ける
    default:                                // それ以外の場合
        printf("aかbを入力してください\n"); // エラーメッセージを表示する
        break;                              // switch文から抜ける
    }
    return 0;
}