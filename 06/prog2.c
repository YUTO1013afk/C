#include <stdio.h>
#include <string.h>

void reverseString(char *);
int my_strlen(char *);

int main() {
    char message[] = "Hello, World!";
    printf("Before: %s\n", message);
    reverseString(message);
    printf("After : %s\n", message);
    return 0;
}

int my_strlen(char *str) {
    int n = 0;
    while (*str++) {
        n++;
    }
    return n;
}

void reverseString(char *str) {
    int len = my_strlen(str);
    char *start = str;
    char *end = str + len - 1;
    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}