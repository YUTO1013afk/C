#include <stdio.h>

int str2int(char *);

int main(int argc, char const *argv[]) {
    char str1[20] = "12345";
    char str2[20] = "+12345";
    char str3[20] = "-12345";
    printf("%s => %d\n", str1, str2int(str1));
    printf("%s => %d\n", str2, str2int(str2));
    printf("%s => %d\n", str3, str2int(str3));
    return 0;
}

int str2int(char *str) {
    int num = 0;  // 数値を格納する変数
    int len = 0;  // ⽂字列の⻑さを格納する変数
    int sign = 1; // 符号を表す変数（1 か -1）

    // ⽂字列の⻑さを求める
    while (str[len] != '\0') {
        len++;
    }

    // ⽂字列の先頭が '-' の場合は符号を -1 にする
    if (str[0] == '-') {
        sign = -1;
        len--; // ⽂字列の⻑さから符号分を引く
        str++; // ⽂字列の先頭を次の⽂字に移動する
    }
    // ⽂字列の先頭が '+' の場合は符号を 1 にする
    else if (str[0] == '+') {
        sign = 1;
        len--; // ⽂字列の⻑さから符号分を引く
        str++; // ⽂字列の先頭を次の⽂字に移動する
    }

    // ⽂字列の各桁を数値に変換して num に加算する
    for (int i = 0; i < len; i++) {
        // ⽂字が '0' から '9' の範囲内でなければエラーとする
        if (str[i] < '0' || str[i] > '9') {
            printf("エラー: 数字以外の⽂字が含まれています。\n");
            return 0;
        }
        // 10 の (len - i - 1) 乗を求める
        int power = 1; // 結果を格納する変数
        for (int j = 0; j < len - i - 1; j++) {
            power *= 10; // power に 10 をかける
        }
        // power を num に加算する
        num += (str[i] - '0') * power;
    }

    // 符号をかけて返す
    return num * sign;
}
