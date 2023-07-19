#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define DATA_SIZE 100000

long data[DATA_SIZE];

// スレッド関数として定義した配列初期化関数
void *init_function(void *arg) {
    struct arg_struct {
        int thread_num;
        long *array;
    };

    // 引数からスレッド番号と配列ポインターを取得
    int thread_num = ((struct arg_struct *)arg)->thread_num;
    long *array = ((struct arg_struct *)arg)->array;

    // スレッド番号に応じて配列の前半または後半を初期化
    int start = thread_num * (DATA_SIZE / 2);
    int end = start + (DATA_SIZE / 2);
    for (int i = start; i < end; i++) {
        array[i] = i;
        usleep(100);
    }
    return NULL;
}

int main(int argc, char const *argv[]) {
    struct timespec start_time, end_time;
    unsigned int sec;
    int nsec;
    double d_sec;
    clock_gettime(CLOCK_REALTIME, &start_time);

    // 2つのpthread_t型の変数を宣言
    pthread_t thread1, thread2;

    // スレッド関数に渡す引数（構造体）を作成
    struct arg_struct {
        int thread_num;
        long *array;
    };

    struct arg_struct arg1, arg2;
    arg1.thread_num = 0;
    arg1.array = data;
    arg2.thread_num = 1;
    arg2.array = data;

    // pthread_create関数で2つのスレッドを作成
    pthread_create(&thread1, NULL, init_function, (void *)&arg1);
    pthread_create(&thread2, NULL, init_function, (void *)&arg2);

    // pthread_join関数で2つのスレッドが終了するまで待機
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    clock_gettime(CLOCK_REALTIME, &end_time);
    // 処理中の経過時間を計算
    sec = end_time.tv_sec - start_time.tv_sec;
    nsec = end_time.tv_nsec - start_time.tv_nsec;
    d_sec = (double)sec + (double)nsec / (1000 * 1000 * 1000);
    // 計測時間の表示
    printf("time:%f\n", d_sec);
    return 0;
}