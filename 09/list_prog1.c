#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 構造体の定義
struct Student {
    int class_number; // クラス番号
    char name[20];    // ⽒名
    int japanese;     // 国語の点数
    int math;         // 数学の点数
    int english;      // 英語の点数
};

struct Node {
    struct Student data; // 構造体のデータ
    struct Node *next;   // 次のノードへのポインタ
};

// 関数のプロトタイプ宣言
struct Node *createNode(int class_number, char *name, int japanese, int math, int english);
void append(struct Node *head, struct Node *node);
void display(struct Node *head);
void total(struct Node *head);
struct Node *findMax(struct Node *head, char *subject);
void display_one(struct Node *node);

// メイン関数
int main(int argc, char const *argv[]) {
    struct Node *head, *data;
    head = createNode(1, "Endou", 80, 80, 70);
    data = createNode(20, "Okita", 60, 95, 50);
    append(head, data);
    data = createNode(4, "Amano", 70, 70, 70);
    append(head, data);
    data = createNode(9, "Inoue", 50, 90, 90);
    append(head, data);
    data = createNode(11, "Ueda", 85, 90, 60);
    append(head, data);

    display(head); // データを表示する
    printf("\n");
    printf("合計点\n");
    total(head); // 合計点を計算して表示する
    printf("\n");
    printf("国語の最⾼点\n");
    display_one(findMax(head, "国語")); // 国語の最⾼点を探して表示する
    printf("\n");
    printf("数学の最⾼点\n");
    display_one(findMax(head, "数学")); // 数学の最⾼点を探して表示する
    printf("\n");
    printf("英語の最⾼点\n");
    display_one(findMax(head, "英語")); // 英語の最⾼点を探して表示する

    return 0;
}

// 関数の定義
struct Node *createNode(int class_number, char *name, int japanese, int math, int english) {
    struct Node *node = (struct Node *)malloc(sizeof(struct Node)); // ノードのメモリ確保
    node->data.class_number = class_number;                         // クラス番号をコピー
    strcpy(node->data.name, name);                                  // ⽒名をコピー
    node->data.japanese = japanese;                                 // 国語の点数をコピー
    node->data.math = math;                                         // 数学の点数をコピー
    node->data.english = english;                                   // 英語の点数をコピー
    node->next = NULL;                                              // 次のノードへのポインタをNULLに設定
    return node;                                                    // ノードを返す
}

void append(struct Node *head, struct Node *node) {
    struct Node *current = head;    // 先頭ノードから始める
    while (current->next != NULL) { // 次のノードがNULLでない間繰り返す
        current = current->next;    // 次のノードに移動する
    }
    current->next = node; // 追加するノードを接続する
}

void display(struct Node *head) {
    struct Node *current = head;                                                                                                                                                           // 先頭ノードから始める
    printf("No\t⽒名\t国語\t数学\t英語\t現在のアドレス\t次のアドレス\n");                                                                                                                  // ヘッダーを出力する
    while (current != NULL) {                                                                                                                                                              // 現在のノードがNULLでない間繰り返す
        printf("%d\t%s\t%d\t%d\t%d\t%p\t%p\n", current->data.class_number, current->data.name, current->data.japanese, current->data.math, current->data.english, current, current->next); // 現在のノードのデータとアドレスを出力する
        current = current->next;                                                                                                                                                           // 次のノードに移動する
    }
}

void total(struct Node *head) {
    struct Node *current = head;                                                                                                                                                                                                                                    // 先頭ノードから始める
    printf("No\t⽒名\t国語\t数学\t英語\t得点計\t現在のアドレス\t次のアドレス\n");                                                                                                                                                                                   // ヘッダーを出力する
    while (current != NULL) {                                                                                                                                                                                                                                       // 現在のノードがNULLでない間繰り返す
        printf("%d\t%s\t%d\t%d\t%d\t%d\t%p\t%p\n", current->data.class_number, current->data.name, current->data.japanese, current->data.math, current->data.english, current->data.japanese + current->data.math + current->data.english, current, current->next); // 番号、⽒名、各科目の点数、合計点、アドレスを出力する
        current = current->next;                                                                                                                                                                                                                                    // 次のノードに移動する
    }
}

// 教科名とノードを受け取り、点数を返す関数
int getScore(char *subject, struct Node *node) {
    if (strcmp(subject, "国語") == 0) {        // 教科名が国語なら
        return node->data.japanese;            // 国語の点数を返す
    } else if (strcmp(subject, "数学") == 0) { // 教科名が数学なら
        return node->data.math;                // 数学の点数を返す
    } else if (strcmp(subject, "英語") == 0) { // 教科名が英語なら
        return node->data.english;             // 英語の点数を返す
    } else {
        printf("教科名が不正です。\n"); // 教科名が不正ならエラーメッセージを出力する
        return -1;                      // -1を返す
    }
}

struct Node *findMax(struct Node *head, char *subject) {
    struct Node *current = head;            // 先頭ノードから始める
    struct Node *maxNode = head;            // 最⾼点のノードを先頭ノードに仮定する
    int maxScore = 0;                       // 最⾼点を0に初期化する
    int score;                              // 点数を格納する変数
    while (current != NULL) {               // 現在のノードがNULLでない間繰り返す
        score = getScore(subject, current); // 教科名とノードから点数を取得する
        if (score == -1) {                  // 点数が-1なら
            return NULL;                    // NULLを返す
        }
        if (score > maxScore) { // 点数が最⾼点より大きければ
            maxScore = score;   // 最⾼点を更新する
            maxNode = current;  // 最⾼点のノードを更新する
        }
        current = current->next; // 次のノードに移動する
    }
    return maxNode; // 最⾼点のノードを返す
}

void display_one(struct Node *node) {
    printf("No\t⽒名\t国語\t数学\t英語\t現在のアドレス\t次のアドレス\n");
    printf("%d\t%s\t%d\t%d\t%d\t%p\t%p\n", node->data.class_number, node->data.name, node->data.japanese, node->data.math, node->data.english, node, node->next); // 番号、⽒名、各科目の点数、アドレスを出力する
}
