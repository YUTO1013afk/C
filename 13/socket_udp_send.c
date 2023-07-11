#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#define SERVER_PORT 60002
void usage(const char *);
int main(int argc, char const *argv[]) {
    const char *server_ip;
    if (argc != 2) {
        usage(argv[0]);
    } else {
        server_ip = argv[1];
    }
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, server_ip, &addr.sin_addr.s_addr);
    char message[] = "Hello, World";
    ssize_t n;
    n = sendto(sockfd, message, strlen(message), 0, (struct sockaddr *)&addr, sizeof(addr));
    if (n < 1) {
        perror("sendto");
        exit(1);
    }
    close(sockfd);
    return 0;
}
void usage(const char *msg) {
    printf("使⽤⽅法：%s IPアドレス\n", msg);
    exit(1);
}