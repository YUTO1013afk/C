#include <stdio.h>

// 構造体 Book の定義と typedef
typedef struct {
    char title[50];
    char author[50];
    int year;
    float price;
} Book; // 構造体の型名を Book にする

int main() {
    // 構造体 Book 型の配列 books を宣言
    Book books[10]; // 型名を Book にする

    // 標準入力から本の情報を入力
    printf("本の情報を⼊⼒してください\n");
    printf("タイトル: ");
    scanf("%49s", books[0].title); // 文字列は %s 変換指定子と配列名で入力
    printf("著者名: ");
    scanf("%49s", books[0].author);
    printf("出版年: ");
    // scanf の戻り値をチェック
    while (scanf("%d", &books[0].year) != 1 || books[0].year <= 0) {
        printf("正の整数を入力してください\n"); // エラーメッセージを表示
        while (getchar() != '\n'); // バッファをクリア
        printf("出版年: ");
    }
    printf("価格: ");
    // scanf の戻り値をチェック
    while (scanf("%f", &books[0].price) != 1 || books[0].price <= 0) {
        printf("正の整数を入力してください\n"); // エラーメッセージを表示
        while (getchar() != '\n'); // バッファをクリア
        printf("価格: ");
    }
    printf("\n");

    // 配列 books の各要素から本の情報を表示
    printf("== 本の情報 ==\n");
    for (int i = 0; i < 1; i++) {                 // 入力した回数だけループする
        printf("タイトル: %s\n", books[i].title); // 配列の要素に直接アクセスする
        printf("著者名: %s\n", books[i].author);
        printf("出版年: %d\n", books[i].year);
        printf("価格: %.2f 円\n", books[i].price);
        printf("\n");
    }

    return 0;
}