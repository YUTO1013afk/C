struct Rectangle {
    int width;
    int height;
};

// ポインタを使⽤して関数内で構造体の幅と⾼さを2倍に更新する関数
void doubleSize(struct Rectangle *rect) {
    rect->width *= 2;  // 幅を2倍にする
    rect->height *= 2; // 高さを2倍にする
}

int main() {
    struct Rectangle r = {10, 20};                                  // 構造体変数rを初期化
    printf("Before: width = %d, height = %d\n", r.width, r.height); // 変更前の値を表示
    doubleSize(&r);                                                 // 関数に構造体変数rのアドレスを渡す
    printf("After: width = %d, height = %d\n", r.width, r.height);  // 変更後の値を表示
    return 0;
}
