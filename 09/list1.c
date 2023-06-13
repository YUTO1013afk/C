#include <stdio.h>
#include <stdlib.h>

// 単⽅向リストの要素を表す構造体
typedef struct Node {
    int data;
    struct Node *next;
} Node;
// プロトタイプ宣⾔
Node *createNode(int);
void append(Node *, Node *);
void display(Node *);
int main(int argc, char const *argv[]) {
    Node *head = NULL;
    Node *data;
    head = createNode(100);
    display(head);
    data = createNode(200);
    append(head, data);
    data = createNode(300);
    append(head, data);
    display(head);
    return 0;
}
Node *createNode(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}
void append(Node *head, Node *newNode) {
    Node *current = head;

    // 終わりのNodeを探す
    while (current->next != NULL) {
        current = current->next;
    }

    // 新しいNodeを追加する
    current->next = newNode;
}

void display(Node *head) {
    Node *current = head;
    printf("現在のアドレス\t次のアドレス\t値\n");
    while (current != NULL) {
        printf("%p\t%p\t%d\n", current, current->next, current->data);
        // printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}