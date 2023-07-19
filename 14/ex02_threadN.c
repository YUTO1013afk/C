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
        int start;
        int end;
    };

    // 引数からスレッド番号、配列ポインター、処理範囲を取得
    struct arg_struct *args = (struct arg_struct *)arg;
    int thread_num = args->thread_num;
    long *array = args->array;
    int start = args->start;
    int end = args->end;

    // 配列の一部を初期化
    for (int i = start; i < end; i++) {
        array[i] = i;
        usleep(100);
    }
    return NULL;
}

int main(int argc, char const *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <num_threads>\n", argv[0]);
        return 1;
    }

    int num_threads = atoi(argv[1]);
    if (num_threads <= 0) {
        printf("Invalid number of threads\n");
        return 1;
    }

    struct timespec start_time, end_time;
    unsigned int sec;
    int nsec;
    double d_sec;
    clock_gettime(CLOCK_REALTIME, &start_time);

    // pthread_t型の変数を宣言
    pthread_t threads[num_threads];

    // スレッド関数に渡す引数（構造体）を作成
    struct arg_struct {
        int thread_num;
        long *array;
        int start;
        int end;
    };

    struct arg_struct args[num_threads];
    int range = DATA_SIZE / num_threads;
    for (int i = 0; i < num_threads; i++) {
        args[i].thread_num = i;
        args[i].array = data;
        args[i].start = i * range;
        args[i].end = args[i].start + range;
    }
    args[num_threads - 1].end = DATA_SIZE; // 最後のスレッドの処理範囲を調整

    // スレッドを作成
    for (int i = 0; i < num_threads; i++) {
        pthread_create(&threads[i], NULL, init_function, (void *)&args[i]);
    }

    // 全てのスレッドが終了するまで待機
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    clock_gettime(CLOCK_REALTIME, &end_time);
    // 処理中の経過時間を計算
    sec = end_time.tv_sec - start_time.tv_sec;
    nsec = end_time.tv_nsec - start_time.tv_nsec;
    d_sec = (double)sec + (double)nsec / (1000 * 1000 * 1000);
    // 計測時間の表示
    printf("time:%f\n", d_sec);
    return 0;
}
