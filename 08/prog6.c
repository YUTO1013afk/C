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
    printf("長方形の情報を入力してください\n");
    printf("幅: ");
    scanf("%lf", &rect.width); // 実数は %lf 変換指定子と変数のアドレスで入力
    printf("高さ: ");
    scanf("%lf", &rect.height);
    printf("\n");

    // 関数 calcArea と calcPerimeter を呼び出して面積と周囲の長さを表示
    printf("== 長方形の情報 ==\n");
    printf("面積: %.2f\n", calcArea(&rect));            // 変数 rect のアドレスを渡す
    printf("周囲の長さ: %.2f\n", calcPerimeter(&rect)); // 変数 rect のアドレスを渡す

    return 0;
}
