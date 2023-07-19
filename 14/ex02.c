#include <stdio.h>
#define DATA_SIZE 100000
long data[DATA_SIZE];
void init_function(void) {
    for (int i = 0; i < DATA_SIZE; i++) {
        data[i] = i;
    }
    return;
}
int main(int argc, char const *argv[]) {
    init_function();
    return 0;
}