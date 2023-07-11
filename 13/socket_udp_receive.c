#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#define SERVER_PORT 60002
#define BUF_SIZE 4096
int main(int argc, char const *argv[]) {
    // ソケットオブジェクトの作成
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket");
        exit(1);
    }
    // IPアドレスとポート番号を作成したソケットオブジェクトに紐づける
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        exit(1);
    }
    // データを受信する
    struct sockaddr_in senderinfo;
    socklen_t addrlen;
    char buffer[BUF_SIZE];
    ssize_t n;
    addrlen = sizeof(senderinfo);
    n = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0,
                 (struct sockaddr *)&senderinfo, &addrlen);
    if (n < 0) {
        perror("recv");
        exit(1);
    }
    // 標準出⼒に受信したデータを表⽰する
    printf("%s\n", buffer);
    // ソケットを閉じる
    close(sockfd);
    return 0;
}