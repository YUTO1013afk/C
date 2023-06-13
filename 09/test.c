// 単⽅向リストの要素を表す構造体
typedef struct Node {
    int data;
    struct Node *next; // 次のNodeを⽰すポインタ
} Node;

void display(Node *head) {
    Node *current = head;
    printf("現在のアドレス\t次のアドレス\t値\n");
    while (current != "") {
        printf("%p\t%p\t%d\n", current, current->next, current->data);
        current = current->next;
    }
    printf("\n");
}
