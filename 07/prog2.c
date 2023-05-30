#include <stdio.h>

int char2int(char);

int main(int argc, char const *argv[]) {
    char ch_a, ch_b;
    
    printf("1桁の数字を⼊⼒してください（1つ⽬）:");
    scanf("%c", &ch_a);
    printf("1桁の数字を⼊⼒してください（2つ⽬）:");
    scanf("\n%c", &ch_b); // 書式に注意
    printf("%c+%c=%d\n", ch_a, ch_b, char2int(ch_a) + char2int(ch_b));
    return 0;
}

int char2int(char ch) {
    return ch - '0'; // 数字⽂字から'0'を引いて数値に変換する
}