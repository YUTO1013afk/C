#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

// 追加
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_ADDR "127.0.0.1"
#define SERVER_PORT 60001
#define BUF_SIZE 4096

int main(int argc, char const *argv[]) {
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
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_ADDR);

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        exit(1);
    }

    // サーバからデータを受信する
    char buffer[BUF_SIZE];
    int n = recv(sockfd, buffer, sizeof(buffer)-1, 0);
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
