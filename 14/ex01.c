// https://qiita.com/nsnonsugar/items/be8a066c6627ab5b052a
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
unsigned int count_;
void *ThreadA() {
    for (int i = 0; i < 100000; ++i) {
        ++count_;
    }
}
void *ThreadB() {
    for (int i = 0; i < 100000; ++i) {
        ++count_;
    }
}
int main(int argc, char const *argv[]) {
    count_ = 0;
    pthread_t th_a;
    pthread_create(&th_a, NULL, ThreadA, NULL);
    pthread_t th_b;
    pthread_create(&th_b, NULL, ThreadB, NULL);
    pthread_join(th_a, NULL);
    pthread_join(th_b, NULL);
    printf("count_ : %d\n", count_);
    return 0;
}