#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
void *ThreadA() {
    printf("thread A start\n");
    for (int i = 0; i < 100; ++i) {
        printf("A-%d\n", i);
    }
    printf("thread A end\n");
}
void *ThreadB() {
    printf("thread B start\n");
    for (int i = 0; i < 100; ++i) {
        printf("B-%d\n", i);
    }
    printf("thread B end\n");
}

int main(int argc, char const *argv[]) {
    pthread_t th_a;
    pthread_create(&th_a, NULL, ThreadA, NULL);
    pthread_t th_b;
    pthread_create(&th_b, NULL, ThreadB, NULL);
    pthread_join(th_a, NULL);
    pthread_join(th_b, NULL);
    return 0;
}