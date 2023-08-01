#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define NUM_THREAD 3 // 並行処理可能な最大クライアント数
#define PORT 3030    // 適当にポート指定

pthread_mutex_t mutex; // mutex
int busy = -1;         // mutex確保中のスレッドIDを入れる変数

int server_socket(void);
void *accept_loop(void *arg);
void handle_conn(int soc);

// IPv4サーバソケットを作成
int server_socket(void) {
    int soc, opt = 1;
    struct sockaddr_in addr;

    if ((soc = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("[-]socket()");
        exit(1);
    }

    if (setsockopt(soc, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        perror("[-]setsockopt()");
        close(soc);
        exit(1);
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(soc, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("[-]bind()");
        close(soc);
        exit(1);
    }

    if (listen(soc, SOMAXCONN) == -1) { // SOMAXCONNはシステムが接続可能な最大数
        perror("[-]listen()");
        close(soc);
        exit(1);
    }

    return soc;
}

// マルチスレッド化する関数。acceptして次の処理関数をコール
void *accept_thread(void *arg) {
    int soc, acc;
    struct sockaddr_in addr;
    socklen_t len;

    soc = *(int *)arg;
    pthread_detach(pthread_self()); // 終了時にリソース解放する
    for (;;) {
        printf("[+]<%d> Start to lock\n", (int)pthread_self());
        pthread_mutex_lock(&mutex); // mutex確保してaccept待ち
        busy = (int)pthread_self(); // 私がbusy状態だと宣言。自分のスレッドIDを入れる
        printf("[+]<%d> Got lock\n", (int)pthread_self());
        len = (socklen_t)sizeof(addr);
        if ((acc = accept(soc, (struct sockaddr *)&addr, &len)) == -1) {
            perror("[-]accept()");
            printf("[-]<%d> Release lock\n", (int)pthread_self());
            busy = -1;
            pthread_mutex_unlock(&mutex);
        } else {
            printf("[+]Accept: %s (%d)\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port)); // accept成功したらクライアントのIPとポートを出力
            printf("[+]<%d> Got lock\n", (int)pthread_self());
            busy = -1;                    // mutexの役目終わるのでmutex開いたよ、という
            pthread_mutex_unlock(&mutex); // 実際にmutexアンロック
            handle_conn(acc);             // サーバ側で行う実際の処理。今回は文字を出力する。
            close(acc);
        }
    }

    return (void *)0;
}

// 処理関数(クライアントが入力した文字をサーバ側は標準出力)
void handle_conn(int acc) {
    int len;
    char *buf;

    buf = (char *)malloc(1024);
    for (;;) {
        if ((len = recv(acc, buf, 1, 0)) == -1) { // 1文字ずつ受信する
            perror("[-]recv()");
            break;
        } else {
            if (*buf == '\n') { // エンター(改行)の場合はbreak
                putchar(*buf);
                break;
            }
            putchar(*buf); // 文字を出力
            buf += 1;      // 次の文字へ
        }
    }
    free(buf);
}

int main(void) {
    int soc;
    pthread_t thread_id;

    soc = server_socket();            // サーバソケット作成
    pthread_mutex_init(&mutex, NULL); // mutexの初期化

    for (int i = 0; i < NUM_THREAD; i++) {
        if (pthread_create(&thread_id, NULL, accept_thread, (void *)&soc) != 0) { // スレッド作成
            perror("[-]pthead_create()");
        } else {
            printf("[+]pthread_created: thread_id = %d\n", (int)thread_id);
        }
    }
    printf("[+]Ready for accept...\n");

    // デバッグ用
    for (;;) {
        sleep(10);
        printf("[+]<%d> State: lock: %d\n", getpid(), (int)busy);
    }

    close(soc);
    pthread_mutex_destroy(&mutex); // mutexを破壊
    return 0;
}
