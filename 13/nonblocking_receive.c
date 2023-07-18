#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 60003   // ポート番号
#define BUFSIZE 1024 // バッファーのサイズ

int main(void) {
    int sockfd;                           // ソケットのファイル記述子
    struct sockaddr_in servaddr, cliaddr; // サーバーとクライアントのアドレス構造体
    socklen_t len;                        // アドレス構造体のサイズ
    char buf[BUFSIZE];                    // データ受信用のバッファー
    int n;                                // 受信したバイト数

    // ソケットの作成
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket");
        exit(1);
    }

    // サーバーのアドレス構造体の設定
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY; // ANYからの接続を許可

    // ソケットにアドレスを割り当て
    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind");
        exit(1);
    }

    // クライアントのアドレス構造体のサイズを初期化
    len = sizeof(cliaddr);

    // データの受信ループ
    while (1) {
        // データを受信
        n = recvfrom(sockfd, buf, BUFSIZE, 0, (struct sockaddr *)&cliaddr, &len);
        if (n > 0) {
            // 受信したデータを表示
            buf[n] = '\0';
            printf("Received from %s:%d: %s\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port), buf);
        } else if (n == 0) {
            // クライアントが切断した場合
            printf("Client closed the connection.\n");
            break;
        } else {
            // エラーが発生した場合
            if (errno == EWOULDBLOCK) {
                // データがない場合は「 . 」辺りを表⽰して、受信中であることが分かるようにする
                printf(". ");
                fflush(stdout);
                // sleep()関数を使⽤して、少しwaitをかける
                sleep(1);
                // 動作しているのを確認したら、コメントアウトしても良い
                // continue;
            } else {
                // その他のエラーの場合
                perror("recvfrom");
                exit(1);
            }
        }
    }

    // ソケットを閉じる
    close(sockfd);

    return 0;
}
