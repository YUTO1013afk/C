#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

// 新しいノードを作成する関数
Node *createNode(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// リストの末尾にノードを追加する関数
void append(Node **head, Node *newNode) {
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

// リストの先頭にノードを追加する関数
void prepend(Node **head, Node *newNode) {
    newNode->next = *head;
    *head = newNode;
}

// リストの途中にノードを追加する関数
void insert(Node *head, Node *newNode, int data) {
    Node *current = head;
    while (current != NULL) {
        if (current->data == data) {
            newNode->next = current->next;
            current->next = newNode;
            return;
        }
        current = current->next;
    }
    // 指定されたdataが見つからなかった場合は、最後に追加する
    append(&head, newNode);
}

// リストを表示する関数
void display(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(int argc, char const *argv[]) {
    Node *head = NULL;
    Node *data;
    head = data = createNode(100);
    display(head);
    printf("末尾に追加\n");
    data = createNode(200);
    append(&head, data);
    data = createNode(300);
    append(&head, data);
    display(head);
    printf("先頭に追加\n");
    data = createNode(10);
    prepend(&head, data);
    data = createNode(20);
    prepend(&head, data);
    display(head);
    printf("途中に追加\n");
    data = createNode(-10);
    insert(head, data, 200);
    data = createNode(-20);
    insert(head, data, 999);
    display(head);
    return 0;
}
