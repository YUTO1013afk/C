// https://wireless-network.net/multi-thread-server/
#include <arpa/inet.h>
#include <ctype.h>
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
#define BUF_SIZE 4096

pthread_mutex_t mutex; // mutex
int busy = -1;         // mutex確保中のスレッドIDを入れる変数

// プロトタイプ宣言
int server_socket(void);
void *accept_loop(void *);
void handle_conn(int);
char *tolower_str(char *);

// IPv4サーバソケットを作成
int server_socket(void) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("[-]socket()");
        exit(1);
    }

    // 再実行したときに、"Address already in use" Errorが出ないようにする
    int one = 1;

    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one)) < 0) {
        perror("[-]setsockopt()");
        exit(1);
    }

    // IPアドレスとポート番号を作成したソケットオブジェクトに紐づける
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("[-]bind()");
        exit(1);
    }

    // クライアントからの入力待ち状態になる
    if (listen(sockfd, SOMAXCONN) < 0) { // SOMAXCONNはシステムが接続可能な最大数
        perror("[-]listen()");
        exit(1);
    }

    return sockfd;
}

// マルチスレッド化する関数。acceptして次の処理関数をコール
void *accept_thread(void *arg) {
    int acc;
    struct sockaddr_in addr;
    socklen_t len;

    int sockfd = *(int *)arg;
    pthread_detach(pthread_self()); // 終了時にリソース解放する

    for (;;) {
        printf("[+]<%d> Start to lock\n", (int)pthread_self());
        pthread_mutex_lock(&mutex); // mutex確保してaccept待ち
        busy = (int)pthread_self(); // 私がbusy状態だと宣言。自分のスレッドIDを入れる
        printf("[+]<%d> Got lock\n", (int)pthread_self());
        len = (socklen_t)sizeof(addr);
        if ((acc = accept(sockfd, (struct sockaddr *)&addr, &len)) < 0) {
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

    return NULL;
}

// 処理関数(クライアントが入力した文字をサーバ側は標準出力)
void handle_conn(int acc) {
    int len;
    char *buffer;
    char *ret_msg;

    buffer = (char *)malloc(BUF_SIZE);
    ret_msg = (char *)malloc(BUF_SIZE);

    for (;;) {
        // buffer初期化
        memset(buffer, 0, BUF_SIZE);
        memset(ret_msg, 0, BUF_SIZE);

        if ((len = recv(acc, buffer, BUF_SIZE, 0)) < 0) {
            perror("[-]recv()");
            break;
        }
        printf("%s", buffer);

        // echo出力
        snprintf(ret_msg, BUF_SIZE, "[received] %s", buffer);
        send(acc, ret_msg, strlen(ret_msg), 0);
        // 2回に分けて送信する場合
        // strcpy(ret_msg,"[Recieved] ");
        // send(acc, ret_msg, strlen(ret_msg), 0);
        // send(acc, buffer, strlen(buffer), 0);

        // 小文字に変換
        buffer = tolower_str(buffer);
        // もしくは strcasecmp() を使用するのもあり

        // exit処理
        if (strcmp(buffer, "exit\r\n") == 0) {
            break;
        }
    }
    free(buffer);
    free(ret_msg);
}

char *tolower_str(char *str) {
    for (char *p = str; *p != '\0'; ++p) {
        *p = tolower(*p);
    }
    return str;
}

int main(void) {

    int sockfd;
    pthread_t thread_id;

    sockfd = server_socket();         // サーバソケット作成
    pthread_mutex_init(&mutex, NULL); // mutexの初期化

    for (int i = 0; i < NUM_THREAD; i++) {
        if (pthread_create(&thread_id, NULL, accept_thread, (void *)&sockfd) != 0) { // スレッド作成
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

    close(sockfd);
    pthread_mutex_destroy(&mutex); // mutexを破壊
    return 0;
}
