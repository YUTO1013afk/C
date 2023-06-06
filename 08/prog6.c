#include <stdio.h>

// 構造体 Rectangle の定義と typedef
typedef struct {
    double width;  // 幅 (実数)
    double height; // 高さ (実数)
} Rectangle;       // 構造体の型名を Rectangle にする

// 構造体 Rectangle 型の変数から面積を計算する関数
double calcArea(Rectangle *r) {
    return r->width * r->height; // 幅と高さの積を返す
}

// 構造体 Rectangle 型の変数から周囲の長さを計算する関数
double calcPerimeter(Rectangle *r) {
    return 2 * (r->width + r->height); // 幅と高さの和の2倍を返す
}

int main() {
    // 構造体 Rectangle 型の変数 rect を宣言
    Rectangle rect;

    // 標準入力から長方形の情報を入力
    printf("長方形の幅と高さを入力してください\n");
    printf("幅: ");
    // scanf の戻り値をチェック
    while (scanf("%lf", &rect.width) != 1 || rect.width <= 0) {
        printf("正の実数を入力してください\n"); // エラーメッセージを表示
        while (getchar() != '\n'); // バッファをクリア
        printf("幅: ");
    }
    printf("高さ: ");
    // scanf の戻り値をチェック
    while (scanf("%lf", &rect.height) != 1 || rect.height <= 0) {
        printf("正の実数を入力してください\n"); // エラーメッセージを表示
        while (getchar() != '\n'); // バッファをクリア
        printf("高さ: ");
    }
    printf("\n");

    // 関数 calcArea と calcPerimeter を呼び出して面積と周囲の長さを表示
    printf("== 計算結果 ==\n");
    printf("面積: %.2f\n", calcArea(&rect));            // 変数 rect のアドレスを渡す
    printf("周囲の長さ: %.2f\n", calcPerimeter(&rect)); // 変数 rect のアドレスを渡す

    return 0;
}