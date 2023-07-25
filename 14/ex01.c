// https://qiita.com/nsnonsugar/items/be8a066c6627ab5b052a
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
unsigned int count_;
pthread_mutex_t mutex; // mutex変数を宣言する
void *ThreadA() {
    for (int i = 0; i < 100000; ++i) {
        pthread_mutex_lock(&mutex); // mutexをロックする
        ++count_;
        pthread_mutex_unlock(&mutex); // mutexをアンロックする
    }
}
void *ThreadB() {
    for (int i = 0; i < 100000; ++i) {
        pthread_mutex_lock(&mutex); // mutexをロックする
        ++count_;
        pthread_mutex_unlock(&mutex); // mutexをアンロックする
    }
}
int main(int argc, char const *argv[]) {
    count_ = 0;
    pthread_mutex_init(&mutex, NULL); // mutex変数を初期化する
    pthread_t th_a;
    pthread_create(&th_a, NULL, ThreadA, NULL);
    pthread_t th_b;
    pthread_create(&th_b, NULL, ThreadB, NULL);
    pthread_join(th_a, NULL);
    pthread_join(th_b, NULL);
    printf("count_ : %d\n", count_);
    pthread_mutex_destroy(&mutex); // mutex変数を破棄する
    return 0;
}
