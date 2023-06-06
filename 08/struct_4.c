#include <stdio.h>
struct Student {
    int no;
    char name[20]; // ⽒名
    float height;  // ⾝⻑
    float weight;  // 体重
};
int main(int argc, char const *argv[]) {
    struct Student nf[] = {
        {1, "Arita", 165.5, 62.2},
        {2, "Inoue", 170.2, 67.3},
        {3, "Ueda", 168.7, 66.4},
    };
    struct Student *p = nf;
    for (int i = 0; i < (sizeof(nf) / sizeof(struct Student)); i++) {
        printf("%d : %s\n", (p + i)->no, (p + i)->name);
    }
    return 0;
}