// 【図解あり】ソケット通信の仕組みについてわかりやすく解説(python)
// https://envader.plus/article/27
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

// 追加
// inet_ntoa() / inet_addr() は arpa/inet.h
#include <arpa/inet.h>

// close()
#include <unistd.h>

#define BUF_SIZE 4096

int main(int argc, char const *argv[]) {
    // コマンドライン引数のチェック
    if (argc < 3) {
        fprintf(stderr, "Usage: %s ip_address port_number\n", argv[0]);
        exit(1);
    }

    // ソケットオブジェクトの作成
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket");
        exit(1);
    }

    // 再実行したときに、"Address already in use" Errorが出ないようにする
    int one = 1;

    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const char *)&one, sizeof(int)) < 0) {
        perror("setsockopt");
        exit(1);
    }

    // IPアドレスとポート番号を作成したソケットオブジェクトに紐づける
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    // コマンドライン引数からIPアドレスとポート番号を取得する
    addr.sin_port = htons(atoi(argv[2]));
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind");
        exit(1);
    }

    // クライアントからの入力待ち状態になる
    if (listen(sockfd, 1) < 0) {
        perror("listen");
        exit(1);
    }

    int count = 0;
    while (count < 5) {

        // クライアントからの接続を受け付ける
        int connfd;
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        if ((connfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_addr_len)) < 0) {
            perror("accept");
            exit(1);
        }

        // サーバの標準出力に文字列を出す
        char buffer[BUF_SIZE];
        snprintf(buffer, sizeof(buffer), "Source IP Address: %s", inet_ntoa(client_addr.sin_addr));
        printf("%s\n", buffer);

        // クライアントのソケットにデータを送信する
        char message[] = "Hello World!";
        send(connfd, message, strlen(message), 0);

        // クライアントのソケットオブジェクトを削除する
        close(connfd);
        count++;
    }
    // サーバのソケットを削除する
    close(sockfd);

    return 0;
}
