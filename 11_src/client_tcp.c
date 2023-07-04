#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#define SERVER_IP "127.0.0.1" // サーバのIPアドレス
#define SERVER_PORT 60001     // サーバのポート番号

int main(void) {
    int sock;                       // ソケットのファイルディスクリプター
    struct sockaddr_in server_addr; // サーバのアドレス情報
    char buffer[4096];              // データの受信用バッファー
    int recv_len;                   // 受信したデータの長さ

    // ホストのソケットオブジェクトの作成
    sock = socket(AF_INET, SOCK_STREAM, 0); // TCP通信用のソケットを作成
    if (sock == -1) {                       // ソケット作成に失敗した場合
        perror("socket");                   // エラーメッセージを表示
        exit(1);                            // 終了
    }

    // サーバにリクエストを送る
    memset(&server_addr, 0, sizeof(server_addr));                                    // サーバのアドレス情報を初期化
    server_addr.sin_family = AF_INET;                                                // アドレスファミリーをIPv4に設定
    server_addr.sin_port = htons(SERVER_PORT);                                       // ポート番号をネットワークバイトオーダーに変換して設定
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);                              // IPアドレスを整数値に変換して設定
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) { // サーバに接続要求を送る
        perror("connect");                                                           // エラーメッセージを表示
        exit(1);                                                                     // 終了
    }

    // サーバからデータを受信する
    recv_len = recv(sock, buffer, sizeof(buffer), 0); // ソケットからデータを受信する
    if (recv_len == -1) {                             // 受信に失敗した場合
        perror("recv");                               // エラーメッセージを表示
        exit(1);                                      // 終了
    }

    // クライアントの標準出力に受信したデータを表示する
    printf("%s\n", buffer);

    // クライアントのソケットを削除する

    close(sock); // ソケットを閉じる

    return 0;
}
