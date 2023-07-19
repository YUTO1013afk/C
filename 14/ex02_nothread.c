#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#define DATA_SIZE 100000
long data[DATA_SIZE];
void init_function(void) {
    for (int i = 0; i < DATA_SIZE; i++) {
        data[i] = i;
        usleep(100);
    }
    return;
}
int main(int argc, char const *argv[]) {
    struct timespec start_time, end_time;
    unsigned int sec;
    int nsec;
    double d_sec;
    clock_gettime(CLOCK_REALTIME, &start_time);
    init_function();
    clock_gettime(CLOCK_REALTIME, &end_time);
    // 処理中の経過時間を計算
    sec = end_time.tv_sec - start_time.tv_sec;
    nsec = end_time.tv_nsec - start_time.tv_nsec;
    d_sec = (double)sec + (double)nsec / (1000 * 1000 * 1000);
    // 計測時間の表⽰
    printf("time:%f\n", d_sec);
    return 0;
}