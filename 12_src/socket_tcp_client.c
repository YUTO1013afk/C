#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

// 追加
#include <arpa/inet.h>
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

    // サーバにリクエストを送る
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    // コマンドライン引数からIPアドレスとポート番号を取得する
    server_addr.sin_port = htons(atoi(argv[2]));
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        exit(1);
    }

    // サーバからデータを受信する
    char buffer[BUF_SIZE];
    int n = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
    if (n < 0) {
        perror("recv");
        exit(1);
    }

    // クライアントの標準出力に受信したデータを表示する
    printf("%s\n", buffer);

    // ソケットを閉じる
    close(sockfd);

    return 0;
}
